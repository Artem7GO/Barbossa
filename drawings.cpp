#include "main.h"
cdrawings* draw = new cdrawings();
cwindow* window = new cwindow();

HFONT framefont, espfont;
bool bWasPressed, bWasReleased;

typedef struct
{
    char    m_szDefinition[ 12 ];
    char    m_szShiftDefinition[ 12 ];
    char    m_szAltDefinition[ 12 ];
}KeyStroke_t;

Color ColorBasedOnFlags(IFlags& flag) {
    Color col = [&]() -> Color {
        if(flag == IFlags::IFLAG_DANGER)
            return Color(178, 13, 68, 255);
        else if(flag == IFlags::IFLAG_INFO)
            return Color(13, 159, 178, 255);
        else if(flag == IFlags::IFLAG_SUCCESS)
            return Color(25, 197, 151, 255);
        else if(flag == IFlags::IFLAG_WARNING)
            return Color(184, 186, 29, 255);
        else if(flag == IFlags::IFLAG_DEFAULT)
            return Color(160, 160, 160, 255);
    }();
    
    return col;
}



int activeIndex = 0;

KeyStroke_t m_KeyStroke[MOUSE_COUNT + KEY_COUNT] = {
    { "", "", "" },
    { "0", "=", "}" },			//KEY_0
    { "1", "!", "" },			//KEY_1
    { "2", "'", "" },			//KEY_2
    { "3", "", "" },			//KEY_3
    { "4", "$", "" },			//KEY_4
    { "5", "%", "" },			//KEY_5
    { "6", "&", "" },			//KEY_6
    { "7", "/", "{" },			//KEY_7
    { "8", "(", "[" },			//KEY_8
    { "9", ")", "]" },			//KEY_9
    { "a", "A", "" },			//KEY_A,
    { "b", "B", "" },			//KEY_B,
    { "c", "C", "" },			//KEY_C,
    { "d", "D", "" },			//KEY_D,
    { "e", "E", "" },			//KEY_E,
    { "f", "F", "" },			//KEY_F,
    { "g", "G", "" },			//KEY_G,
    { "h", "H", "" },			//KEY_H,
    { "i", "I", "" },			//KEY_I,
    { "j", "J", "" },			//KEY_J,
    { "k", "K", "" },			//KEY_K,
    { "l", "L", "" },			//KEY_L,
    { "m", "M", "" },			//KEY_M,
    { "n", "N", "" },			//KEY_N,
    { "o", "O", "" },			//KEY_O,
    { "p", "P", "" },			//KEY_P,
    { "q", "Q", "" },			//KEY_Q,
    { "r", "R", "" },			//KEY_R,
    { "s", "S", "" },			//KEY_S,
    { "t", "T", "" },			//KEY_T,
    { "u", "U", "" },			//KEY_U,
    { "v", "V", "" },			//KEY_V,
    { "w", "W", "" },			//KEY_W,
    { "x", "X", "" },			//KEY_X,
    { "y", "Y", "" },			//KEY_Y,
    { "z", "Z", "" },			//KEY_Z,
    { "0", "0", "" },			//KEY_PAD_0,
    { "1", "1", "" },			//KEY_PAD_1,
    { "2", "2", "" },			//KEY_PAD_2,
    { "3", "3", "" },			//KEY_PAD_3,
    { "4", "4", "" },			//KEY_PAD_4,
    { "5", "5", "" },			//KEY_PAD_5,
    { "6", "6", "" },			//KEY_PAD_6,
    { "7", "7", "" },			//KEY_PAD_7,
    { "8", "8", "" },			//KEY_PAD_8,
    { "9", "9", "" },			//KEY_PAD_9,
    { "/", "/", "" },			//KEY_PAD_DIVIDE,
    { "*", "*", "" },			//KEY_PAD_MULTIPLY,
    { "-", "-", "" },			//KEY_PAD_MINUS,
    { "+", "+", "" },			//KEY_PAD_PLUS,
    { "enter", "enter", "" },				//KEY_PAD_ENTER,
    { ".", ">", "" },				//KEY_PAD_DECIMAL,
    { "[", "{", "" },				//KEY_LBRACKET,
    { "]", "}", "" },				//KEY_RBRACKET,
    { ";", ":", "" },				//KEY_SEMICOLON,
    { "'", "@", "" },				//KEY_APOSTROPHE,
    { "`", "", "" },				//KEY_BACKQUOTE,
    { ",", "<", "" },				//KEY_COMMA,
    { ".", ">", "" },				//KEY_PERIOD,
    { "/", "?", "" },				//KEY_SLASH,
    { "\\", "|", "" },				//KEY_BACKSLASH,
    { "-", "_", "" },				//KEY_MINUS,
    { "=", "+", "" },				//KEY_EQUAL,
    { "enter", "enter", "" },				//KEY_ENTER,
    { "space", "space", "" },				//KEY_SPACE,
    { "backspace", "backspace", "" },				//KEY_BACKSPACE,
    { "tab", "tab", "" },				//KEY_TAB,
    { "caps", "caps", "" },				//KEY_CAPSLOCK,
    { "numlock", "numlock", "" },				//KEY_NUMLOCK,
    { "escape", "escape", "" },				//KEY_ESCAPE,
    { "scrlock", "scrlock", "" },				//KEY_SCROLLLOCK,
    { "insert", "insert", "" },				//KEY_INSERT,
    { "delete", "delete", "" },				//KEY_DELETE,
    { "home", "home", "" },				//KEY_HOME,
    { "end", "end", "" },				//KEY_END,
    { "pageup", "pageup", "" },				//KEY_PAGEUP,
    { "pagedown", "pagedown", "" },				//KEY_PAGEDOWN,
    { "break", "break", "" },				//KEY_BREAK,
    { "lshift", "lshift", "" },				//KEY_LSHIFT,
    { "rshift", "rshift", "" },				//KEY_RSHIFT,
    { "lalt", "lalt", "" },				//KEY_LALT,
    { "ralt", "ralt", "" },				//KEY_RALT,
    { "lctrl", "lctrl", "" },				//KEY_LCONTROL,
    { "rctrl", "rctrl", "" },				//KEY_RCONTROL,
    { "lwin", "lwin", "" },				//KEY_LWIN,
    { "rwin", "rwin", "" },				//KEY_RWIN,
    { "app", "app", "" },				//KEY_APP,
    { "up", "up", "" },				//KEY_UP,
    { "left", "left", "" },				//KEY_LEFT,
    { "down", "down", "" },				//KEY_DOWN,
    { "right", "right", "" },				//KEY_RIGHT,
    { "f1", "f1", "" },				//KEY_F1,
    { "f2", "f2", "" },				//KEY_F2,
    { "f3", "f3", "" },				//KEY_F3,
    { "f4", "f4", "" },				//KEY_F4,
    { "f5", "f5", "" },				//KEY_F5,
    { "f6", "f6", "" },				//KEY_F6,
    { "f7", "f7", "" },				//KEY_F7,
    { "f8", "f8", "" },				//KEY_F8,
    { "f9", "f9", "" },				//KEY_F9,
    { "f10", "f10", "" },			//KEY_F10,
    { "f11", "f11", "" },			//KEY_F11,
    { "f12", "f12", "" },				//KEY_F12,
    { "caps", "capstoggle", "" },				//KEY_CAPSLOCKTOGGLE,
    { "numlock", "numlock", "" },				//KEY_NUMLOCKTOGGLE,
    { "scrlock", "scrlock", "" },				//KEY_SCROLLLOCKTOGGLE,
    
    // Mouse
    { "mouse1", "mouse1", "" },				//MOUSE_LEFT = MOUSE_FIRST,
    { "mouse2", "mouse2", "" },				//MOUSE_RIGHT,
    { "mouse3", "mouse3", "" },				//MOUSE_MIDDLE,
    { "mouse4", "mouse4", "" },				//MOUSE_4,
    { "mouse5", "mouse5", "" },				//MOUSE_5,
    { "mwheelup", "mwheelup", "" },				//MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up
    { "mwheeldown", "mwheeldown", "" },				//MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down
};

auto WasPressed (ButtonCode_t code) -> void {
    if (pInputSystem->IsButtonDown(code))
    {
        bWasPressed = true;
    }
    else if (!(pInputSystem->IsButtonDown(code)))
    {
        if (bWasPressed)
            bWasReleased = true;
        else
        {
            bWasReleased = false;
        }
        bWasPressed = false;
    }
}

void cwindow::setup(int x, int y, int w, int h) {
    this->x = x, this->y = y, this->w = w, this->h = h;
}

void cwindow::setname(const char *szName) {
    this->szName = szName;
}

const char* cwindow::getname() {
    return this->szName;
}

void cdrawings::drawbox(int x, int y, int w, int h, Color color) {
    pSurface->DrawSetColor(color);
    pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void cdrawings::drawboxoutline(int x, int y, int w, int h, Color color) {
    this->drawbox(x, y, w, h, color);
    this->drawbox(x - 1, y - 1, w + 2, h + 2, Color(0, 0, 0, 180));
    this->drawbox(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, 180));
}

void cdrawings::fillrgba(int x, int y, int w, int h, Color color) {
    pSurface->DrawSetColor(color);
    pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void cdrawings::drawline(int x, int y, int xx, int yy, Color color) {
    pSurface->DrawSetColor(color);
    pSurface->DrawLine(x, y, xx, yy);
}

std::wstring cdrawings::wstringtostring(std::string str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    
    try
    {
        return converter.from_bytes(str);
    }
    catch (std::range_error)
    {
        std::wostringstream s;
        s << str.c_str();
        return s.str();
    }
}

HFONT cdrawings::createfont(HFONT font, const char *szFont, int tall, int flags) {
    font = pSurface->CreateFont();
    pSurface->SetFontGlyphSet(font, szFont, tall, 150, 0, 0, flags);
    return font;
}

ViVecMouse::ViVecMouse(void) {
    
}

ViVecMouse::ViVecMouse(int X, int Y) {
    x = X; y = Y;
}

ViVecMouse cdrawings::GetMouse() {
    int x, y;
    pInputSystem->GetCursorPosition(&x, &y);
    
    ViVecMouse pPosition = ViVecMouse(x, y);
    return pPosition;
}

int cdrawings::CalcPos(int x) { // Not really sure who made this...
    int iRealXStart = ((1920 / 2) - (1920 / 2)) + x;
    return GetMouse().x - iRealXStart;
}

void cdrawings::addslider(int x, int y, int w, const char* szString, int& value, int index, int max, int min) {
    y += index * vars.buttonPadding;
    int h = 10;
    
    // int isCurrent = smoothValue * max - w + x; // DUM DUM VIKING, DUM DUM!
    int isCurrent = value * ((float)w / (float)(max));
    
    if (GetMouse().x > x - w / 2 && GetMouse().y > y - 2 && GetMouse().x < x + w + w / 2 && GetMouse().y < y + h + 2) {
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            value = CalcPos(x) / ((float)w / (float)(max));
            if (value > max)
                value = max;
            if (value < min)
                value = min;
        }
    }
    std::string factor = std::to_string(value);
    std::string tostring = szString;
    
    std::string tofinal = tostring + ": " + factor;
    
    this->fillrgba(x, y, w, h, Color(34, 34, 34, 255));
    this->fillrgba(x + isCurrent, y - 1, 4, h + 2, Color(160, 160, 160, 255));
    this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
    
    this->drawstring(x + w + 3, y - 4, Color(160, 160, 160, 255), framefont, tofinal.c_str());
}

void cdrawings::drawstring(int x, int y, Color color, HFONT font, const char *szString, bool bCenter) {
    if(szString != NULL) {
        std::wstring wString = this->wstringtostring(szString);
        
        if(bCenter) {
            int wide, tall;
            pSurface->GetTextSize(font, wString.c_str(), wide, tall);
            x -= wide / 2;
            y -= tall / 2;
        }
        
        pSurface->DrawSetTextPos(x, y);
        pSurface->DrawSetTextFont(font);
        pSurface->DrawSetTextColor(color);
        pSurface->DrawPrintText(wString.c_str(), wcslen(wString.c_str()));
    }
}

/*
 void fillrgbaINDEX(int x, int y, int w, int h, Color color, int index);
 void drawboxINDEX(int x, int y, int w, int h, Color color, int index);
 void drawstringINDEX(int x, int y, Color color, const char* szString, bool bCenter = false);*/

void cdrawings::fillrgbaINDEX(int x, int y, int w, int h, Color color, int index) {
    y += index * vars.buttonPadding;
    
    fillrgba(x, y, w, h, color);
}

void cdrawings::drawboxINDEX(int x, int y, int w, int h, Color color, int index) {
    y += index * vars.buttonPadding;
    
    drawbox(x, y, w, h, color);
}

void cdrawings::drawstringINDEX(int x, int y, Color color, const char *szString, int index, bool bCenter, IFlags getFlag) {
    y += index * vars.buttonPadding;
    
    drawstring(x, y, ColorBasedOnFlags(getFlag), framefont, szString, bCenter);
}

bool cdrawings::inArea(int x, int y, int w, int h) {
    if(GetMouse().x > x && GetMouse().y > y && GetMouse().x < x + w && GetMouse().y < y + h) {
        return true;
    } else {
        return false;
    }
}



void cdrawings::addcolorslider(int x, int y, int w, const char* szString, int col[4], int index, int max, int min) {
    ///this->addslider(x + 4, y + 50, redesignedWidth, "Fov", vars.aimbot.fov, 2);
    std::string adder = szString;
    
    std::string red = "R";
    std::string green = "G";
    std::string blue = "B";
    std::string alpha = "A";
    
    this->drawstringINDEX(x, y, Color(160, 160, 160, 255), szString, index);
    
    this->addslider(x, y, w, red.c_str(), col[0], index + 1, max, min);
    this->addslider(x, y, w, green.c_str(), col[1], index + 2, max, min);
    this->addslider(x, y, w, blue.c_str(), col[2], index + 3, max, min);
    this->addslider(x, y, w, alpha.c_str(), col[3], index + 4, max, min);
    
    this->fillrgbaINDEX(x, y, 20, 20, Color(col[0], col[1], col[2], col[3]), index + 5);
    this->drawboxINDEX(x, y, 20, 20, Color(160, 160, 160, 255), index + 5);
}

bool cdrawings::inArea2(int x, int y, int xx, int yy) {
    if(GetMouse().x > x && GetMouse().y > y && GetMouse().x < xx && GetMouse().y < yy) {
        return true;
    } else {
        return false;
    }
}

void cdrawings::addbutton(int x, int y, const char* szValue, bool* var, int index, IFlags getFlag) {
    y += index * vars.buttonPadding;
    
    Color state;
    
    int w = 14;
    int h = 14;
    
    if(*var)
        this->fillrgba(x + 2, y + 2, w - 4, h - 4, Color(80, 80, 80, 255));
    
    if(inArea(x, y, w, h)) {
        if(bWasReleased) {
            *var = !*var;
        }
    }
    
    this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
    
    this->drawstring(x + w + 8, y - 1, ColorBasedOnFlags(getFlag), framefont, szValue);
}



void cdrawings::drawgradient(int x, int y, int w, int h, Color col1, Color col2) {
    
        this->fillrgba(x, y, w, h, col1);
        Byte first = col2.r();
        Byte second = col2.g();
        Byte third = col2.b();
        for (int i = 0; i < h; i++)
        {
            float fi = i, fh = h;
            float a = fi / fh;
            int ia = a * 255;
            this->fillrgba(x, y + i, w, 1, Color(first, second, third, ia));
        }
   
}

const char* gettabs() {
    switch(vars.tabIndex) { // going to add more tabs? make sure to add them in a case section.
        case 0:
            return "Aimbot";
            break;
            
        case 1:
            return "Visuals";
            break;
        
        case 2:
            return "Chams";
            break;
        
        case 3:
            return "Removals";
            break;
            
        case 4:
            return "Misc";
            break;
            
        case 5:
            return "Hack VS Hack";
            break;
        
        case 6:
            return "Player List";
            break;
            
        case 7:
            return "Colors";
            break;
            
        default:
            return "Aimbot";
            break;
    }
}

enum tTabs {
    Aimbot,
    Visuals,
    Chams,
    Removals,
    Misc,
    HvH,
    Playerlist,
    Colors
};

void cdrawings::drawnavigation(int x, int y, int w, int h, const char* szString) {

    this->drawgradient(x, y, w, h, Color(33, 33, 33, 255), Color(26, 26, 26, 255));

    
    std::vector<std::string> getTabs;
    
    getTabs.push_back("Aimbot");
    getTabs.push_back("Visuals");
    getTabs.push_back("Chams");
    getTabs.push_back("Removals");
    getTabs.push_back("Misc");
    getTabs.push_back("HvH");
    getTabs.push_back("Playerlist");
    getTabs.push_back("Colors");
    
    
    for(int i = 0; i < getTabs.size(); i++) {
        this->addtabs(x, y, getTabs[i].c_str(), i, vars.tabIndex, getTabs.size());
    }
    
}

void cdrawings::addplayerlistbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString, IFlags getFlag) {
    y += index * vars.buttonPadding;
    
    if(inArea(x, y, w, h)) {
        if(bWasReleased) {
            playercount = index;
        }
    }
    
    bool bHovering = inArea(x, y, w, h);
    this->drawgradient(x, y, w, h, bHovering ? Color(54, 54, 54, 255), Color(34, 34, 34, 255) : Color(44, 44, 44, 255), Color(24, 24, 24, 255));
    this->drawbox(x, y, w, h, Color::Black());
    
    this->drawstring(x + w / 2, y + h / 2, ColorBasedOnFlags(getFlag), framefont, szString, true);
}

void cdrawings::addtabs(int x, int y, const char* szTabs, int index, int& itab, int max) {
    int wScreen, hScreen;
    pEngine->GetScreenSize(wScreen, hScreen);
    
    int w = wScreen / max;
    x += index * w;
    int h = 30;
    
    if(inArea(x, y, w, h)) {
        if(bWasReleased) {
            itab = index;
        }
    }
    
    if(itab == index)
        this->drawgradient(x, y, w, h, Color(36, 123, 149, 255), Color(14, 102, 129, 255));
    
    if(itab == index)
        this->drawstring(x + w / 2, y + h / 2, Color(160, 160, 160, 255), framefont, szTabs, true);
    else
        this->drawstring(x + w / 2, y + h / 2, Color(88, 88, 88, 255), framefont, szTabs, true);
}

void cdrawings::drawpalettetabs(int x, int y, int w, const char* szString, int& itab, int index, int max) {
    w /= max;
    
    x += index * w;
    int h = 20;
    if(inArea(x, y, w, 20)) {
        if(bWasReleased) {
            itab = index;
        }
    }
    
    this->fillrgba(x, y, w, h, Color(64, 64, 64, 255));
    
    if(itab == index)
        this->drawgradient(x, y, w, h, Color(36, 123, 149, 255), Color(14, 102, 129, 255));
    
    if(itab == index)
        this->drawstring(x + w / 2, y + h / 2, Color(160, 160, 160, 255), framefont, szString, true);
    else
        this->drawstring(x + w / 2, y + h / 2, Color(88, 88, 88, 255), framefont, szString, true);
}

bool Janela[8][2];
ViVecMouse ClickPosicao;
bool cdrawings::MoveMenu(int & x, int & y, int w, int h, int index) {
    //Credits: Code64/CodeRed
    for (int i = 0; i < 8; i++)
        if (Janela[i][0] && i != index)
            return false;
    
    if (pInputSystem->IsButtonDown(MOUSE_LEFT))
    {
        /* GetMouse().x > x && GetMouse().x < x + w && GetMouse().y >(y - 3) && GetMouse().y < (y - 3) + h */
        if ((GetMouse().x > x && GetMouse().y > y && GetMouse().x < x + w && GetMouse().y < y + h) || Janela[index][0])
        {
            Janela[index][0] = true;
            
            if (!Janela[index][1])
            {
                ClickPosicao.x = GetMouse().x - x;
                ClickPosicao.y = GetMouse().y - y;
                Janela[index][1] = true;
                
            }
        }
        else
        {
            Janela[index][0] = false;
            Janela[index][1] = false;
        }
    }
    
    if (!(pInputSystem->IsButtonDown(MOUSE_LEFT)) && Janela[index][0])
    {
        Janela[index][0] = false;
        Janela[index][1] = false;
    }
    
    if (Janela[index][0])
    {
        x = GetMouse().x - ClickPosicao.x;
        y = GetMouse().y - ClickPosicao.y;
    }
    
    return true;
}

void cdrawings::drawcolorpicker(int x, int y, const char *szString, Color &col, int index) {
    y += index * vars.buttonPadding;
    int oner = 6;
    float flRnbw = 0.0005f;
    int currPosX, currPosY;
    for(int i = 0 ; i < 21; i++) {
        flRnbw += 0.045f;
        
        Color col1 = Color::GetFromHSB(flRnbw, 1.0f, 1.0f);
        Color col2 = Color::GetFromHSB(flRnbw, 0.90f, 0.90f);
        Color col3 = Color::GetFromHSB(flRnbw, 0.80f, 0.80f);
        Color col4 = Color::GetFromHSB(flRnbw, 0.70f, 0.70f);
        Color col5 = Color::GetFromHSB(flRnbw, 0.60f, 0.60f);
        Color col6 = Color::GetFromHSB(flRnbw, 0.50f, 0.50f);
        Color col7 = Color::GetFromHSB(flRnbw, 0.40f, 0.40f);
        Color col8 = Color::GetFromHSB(flRnbw, 0.30f, 0.30f);
        Color col9 = Color::GetFromHSB(flRnbw, 0.20f, 0.20f);
        Color col10 = Color::GetFromHSB(flRnbw, 0.15f, 0.15f);
        Color col11 = Color::GetFromHSB(flRnbw, 0.10f, 0.10f);
        
        this->fillrgba(x + i * oner, y, oner, oner, Color(col1.r(), col1.g(), col1.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 1, oner, oner, Color(col2.r(), col2.g(), col2.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 2, oner, oner, Color(col3.r(), col3.g(), col3.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 3, oner, oner, Color(col4.r(), col4.g(), col4.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 4, oner, oner, Color(col5.r(), col5.g(), col5.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 5, oner, oner, Color(col6.r(), col6.g(), col6.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 6, oner, oner, Color(col7.r(), col7.g(), col7.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 7, oner, oner, Color(col8.r(), col8.g(), col8.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 8, oner, oner, Color(col9.r(), col9.g(), col9.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 9, oner, oner, Color(col10.r(), col10.g(), col10.b(), 255));
        this->fillrgba(x + i * oner, y + oner * 10, oner, oner, Color(col11.r(), col11.g(), col11.b(), 255));
        
        int x1 = x + i * oner;
        int y2 = y + oner * 1;
        int y3 = y + oner * 2;
        int y4 = y + oner * 3;
        int y5 = y + oner * 4;
        int y6 = y + oner * 5;
        int y7 = y + oner * 6;
        int y8 = y + oner * 7;
        int y9 = y + oner * 8;
        int y10 = y + oner * 9;
        int y11 = y + oner * 10;
        
        if(inArea(x1, y, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col1;
                this->drawbox(x1, y, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y;
            }
        } else if(inArea(x1, y2, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col2;
                this->drawbox(x1, y2, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y2;
            }
        } else if(inArea(x1, y3, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col3;
                this->drawbox(x1, y3, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y3;
            }
        } else if(inArea(x1, y4, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col4;
                this->drawbox(x1, y4, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y4;
            }
        } else if(inArea(x1, y5, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col5;
                this->drawbox(x1, y5, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y5;
            }
        } else if(inArea(x1, y6, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col6;
                this->drawbox(x1, y6, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y6;
            }
        }
        else if(inArea(x1, y7, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col7;
                this->drawbox(x1, y7, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y7;
            }
        }
        else if(inArea(x1, y8, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col8;
                this->drawbox(x1, y8, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y8;
            }
        }
        else if(inArea(x1, y9, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col9;
                this->drawbox(x1, y9, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y9;
            }
        }
        else if(inArea(x1, y10, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col10;
                this->drawbox(x1, y10, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y10;
            }
        }
        else if(inArea(x1, y11, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col11;
                this->drawbox(x1, y11, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y11;
            }
        }
    }
    
    this->fillrgba(x, y + 78, 90, 20, Color(col.r(), col.g(), col.b(), 255));
    this->drawbox(x, y + 78, 90, 20, Color::Black());
    
   // this->drawbox(currPosX, currPosY, oner, oner, Color::Black());
    
    //char tostrcolpalette[308];
    //sprintf(tostrcolpalette, "%s R: %i, G: %i, B: %i", szString, col.r(), col.g(), col.b());
    
    std::string strPalette = szString;
    strPalette.append(" R: ");
    strPalette.append(std::to_string(col.r()));
    
    strPalette.append(" G: ");
    strPalette.append(std::to_string(col.g()));
    
    strPalette.append(" B: ");
    strPalette.append(std::to_string(col.b()));
    
    
    this->drawstring(x, y + 110, Color::White(), framefont, strPalette.c_str());
}

void cdrawings::addcombo(int x, int y, int w, const char* szString, std::vector<std::string> szValue, int& currValue, bool* bOpend, int index) {
    y += index * vars.buttonPadding;
    int h = 15;
    
    if(inArea(x, y, w, h)) {
        if(bWasReleased) {
            *bOpend = !*bOpend;
        }
    }
    
    if(*bOpend) {
        for(int i = 0; i < szValue.size(); i++) {
            int yy = y + h + i * h;
            
            this->fillrgba(x, yy, w, h, Color(34, 34, 34, 255));
            //this->drawbox(x, yy, w, h, Color(134, 134, 134, 255));
            this->drawstring(x + 2, yy - 1, Color(160, 160, 160, 255), framefont, szValue[i].c_str());
            
            if(inArea2(x, yy, x + w, yy + h)) {
                if(bWasReleased) {
                    currValue = i;
                    *bOpend = false;
                }
            }
        }
    }
    
    this->fillrgba(x, y, w, h, Color(34, 34, 34, 255));
    this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
    this->drawstring(x + 2, y - 1, Color(160, 160, 160, 255), framefont, szValue[currValue].c_str());
    this->drawstring(x + w + 3, y - 1, Color(160, 160, 160, 255), framefont, szString);
}

void cdrawings::textbox(int x, int y, int w, const char* szString, std::string szValue[100], int inputIndex, int index, bool* var) {
    y += index * vars.buttonPadding;
    int h = 15;
    
    if(inArea(x, y, w, h)) {
    *var = true;
     activeIndex = inputIndex;
    } else {
    *var = false;
    }
    
    this->fillrgba(x, y, w, h, Color(34, 34, 34, 255));
    if(inArea(x, y, w, h)) {
        this->drawbox(x, y, w, h, Color::Black());
    } else {
        this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
    }
    this->drawstring(x + 2, y - 1, Color(160, 160, 160, 255), framefont, ">");
    
    if(szValue[inputIndex].length() > 32) {
        std::size_t getLength = szValue[inputIndex].length();
        szValue[inputIndex].erase(getLength - 1);
        m_nCurrentPos[inputIndex]--;
    }
    
    if(szValue[inputIndex].length() > 0) {
        this->drawstring(x + 15, y - 1, Color(160, 160, 160, 255), framefont, szValue[inputIndex].c_str());
    }
    
    
    
    this->drawstring(x + w + 3, y - 1, Color(160, 160, 160, 255), framefont, szString);

    
}

void cdrawings::handleinput(int eventcode, string arr[100]) {
    if (IsKeyPressed(eventcode, KEY_BACKSPACE))
    {
        size_t nLength = arr[activeIndex].length();
        if (nLength > 0)
        {
            arr[activeIndex].erase(nLength - 1);
            m_nCurrentPos[activeIndex]--;
            return;
        }
    }
    
    if(IsKeyPressed(eventcode, KEY_ENTER)) {
        m_szChangedValue[activeIndex] = arr[activeIndex];
        return;
    }
    
    if (IsKeyPressed(eventcode, KEY_SPACE))
    {
        arr[activeIndex].append(" ");
        return;
    }
    
    if (eventcode >= KEY_0
        && eventcode <= KEY_EQUAL
        && arr[activeIndex].length() <= 114)
    {
        if (pInputSystem->IsButtonDown(KEY_LSHIFT) || pInputSystem->IsButtonDown(KEY_RSHIFT))
        {
            arr[activeIndex].append(m_KeyStroke[eventcode].m_szShiftDefinition);
            m_nCurrentPos[activeIndex]++;
        }
        else
        {
            arr[activeIndex].append(m_KeyStroke[eventcode].m_szDefinition);
            m_nCurrentPos[activeIndex]++;
        }
    }
}

bool bCheckState() {
    if(pEngine->IsInGame() && pEngine->IsConnected()) {
        return true;
    } else {
        return false;
    }
}

enum cColorTabs {
    CTChams = 0,
    TChams = 1,
    CTBoxes = 2,
    TBoxes = 3,
    HANDChams = 4,
    WEAPCHams = 5,
    World = 6
};

void cdrawings::drawmouse() {
    int mouse_x = this->GetMouse().x;
    int mouse_y = this->GetMouse().y;
    
    this->fillrgba(mouse_x + 1, mouse_y, 1, 17, Color(51, 51, 51, 255));
    
    for(int i = 0; i < 11; i++)
        this->fillrgba(mouse_x + 2 + i, mouse_y + 1 + i, 1, 1, Color(51, 51, 51, 255));
    this->fillrgba(mouse_x + 7, mouse_y + 12, 6, 1, Color(51, 51, 51, 255));
    this->fillrgba(mouse_x + 6, mouse_y + 12, 1, 1, Color(51, 51, 51, 255));
    this->fillrgba(mouse_x + 5, mouse_y + 13, 1, 1, Color(51, 51, 51, 255));
    this->fillrgba(mouse_x + 4, mouse_y + 14, 1, 1, Color(51, 51, 51, 255));
    this->fillrgba(mouse_x + 3, mouse_y + 15, 1, 1, Color(51, 51, 51, 255));
    this->fillrgba(mouse_x + 2, mouse_y + 16, 1, 1, Color(51, 51, 51, 255));
    
    for(int i = 0; i < 4; i++)
        this->fillrgba(mouse_x + 2 + i, mouse_y + 2 + i, 1, 14 - (i * 2), Color(81, 81, 81, 255));
    this->fillrgba(mouse_x + 6, mouse_y + 6, 1, 6, Color(81, 81, 81, 255));
    this->fillrgba(mouse_x + 7, mouse_y + 7, 1, 5, Color(81, 81, 81, 255));
    this->fillrgba(mouse_x + 8, mouse_y + 8, 1, 4, Color(81, 81, 81, 255));
    this->fillrgba(mouse_x + 9, mouse_y + 9, 1, 3, Color(81, 81, 81, 255));
    this->fillrgba(mouse_x + 10, mouse_y + 10, 1, 2, Color(81, 81, 81, 255));
    this->fillrgba(mouse_x + 11, mouse_y + 11, 1, 1, Color(81, 81, 81, 255));
}

void cdrawings::drawmenu() { // This is where we render our menu, add items and so on.
    
    int wScreen, hScreen;
    pEngine->GetScreenSize(wScreen, hScreen);
    
    this->drawnavigation(0, 0, wScreen, 30, "yeet.");
    
    int w = 600, h = 400;
    static int y = 80;
    int hh = 22;
    
    static int rewidth = 130;
    
    this->fillrgba(rewidth, y, w, h, Color(30, 30, 30, 255));
    this->drawbox(rewidth, y, w, h, Color(58, 58, 58, 255));
    this->drawstring(rewidth + 6, y+4, Color(160, 160, 160, 255), framefont, gettabs());
    this->drawline(rewidth, y+22, rewidth + w, y+22, Color(58, 58, 58, 255));
    
    /* Aimbot, Visuals, Chams, Removals, Misc, HvH, Playerlist, Colors */
    
    if(vars.tabIndex == tTabs::Aimbot) {

        this->addbutton(rewidth + 12, y + 30, "Enabled", &vars.aimbot.enabled, 0);
        this->addbutton(rewidth + 12, y + 30, "Silent Aim", &vars.aimbot.silent, 1);
        this->addbutton(rewidth + 12, y + 30, "pSilent Aim", &vars.aimbot.psilent, 2);
        this->addslider(rewidth + 12, y + 30, 90, "Field Of View", vars.aimbot.fov, 3, 180, 0); // 180 and 0... 180 Are the maximum value and 0 is the minimum.
        this->addslider(rewidth + 12, y + 30, 90, "Point Scale", vars.aimbot.pointscale, 4, 100, 0); // 180 and 0... 180 Are the maximum value and 0 is the minimum.
        this->addslider(rewidth + 12, y + 30, 90, "Hitbox", vars.aimbot.bone, 5, 20, 0); // 180 and 0... 180 Are the maximum value and 0 is the minimum.
        this->addbutton(rewidth + 12, y + 30, "Hitscan", &vars.aimbot.hitscan, 6);
        this->addbutton(rewidth + 12, y + 30, "Self Prediction", &vars.aimbot.selfpred, 7);
        this->addbutton(rewidth + 12, y + 30, "Auto Wall", &vars.aimbot.autowall, 8);
        this->addbutton(rewidth + 12, y + 30, "Auto Shoot", &vars.aimbot.autoshoot, 9);
        this->addbutton(rewidth + 12, y + 30, "Auto Pistol", &vars.aimbot.autopistol, 10);
        this->addbutton(rewidth + 12, y + 30, "Auto Stop", &vars.aimbot.autostop, 11);
        this->addbutton(rewidth + 12, y + 30, "Auto Crouch", &vars.aimbot.autocrouch, 12);
    }
    
    if(vars.tabIndex == tTabs::Visuals) {
        this->addbutton(rewidth + 12, y + 30, "Enabled", &vars.visuals.enabled, 0);
        this->addbutton(rewidth + 12, y + 30, "Box", &vars.visuals.box, 1);
        this->addbutton(rewidth + 12, y + 30, "Name", &vars.visuals.name, 2);
        this->addbutton(rewidth + 12, y + 30, "Health", &vars.visuals.health, 3);
        this->addbutton(rewidth + 12, y + 30, "Health Text", &vars.visuals.healthtext, 4);
        this->addbutton(rewidth + 12, y + 30, "Snaplines", &vars.visuals.snapline, 5);
        this->addbutton(rewidth + 12, y + 30, "Skeleton", &vars.visuals.skeleton, 6);
        this->addbutton(rewidth + 12, y + 30, "Hitbox", &vars.visuals.headhitbox, 7);
        this->addbutton(rewidth + 12, y + 30, "Enemy Only", &vars.visuals.enemyonly, 8);
    }
    
    if(vars.tabIndex == tTabs::Chams) {
        std::vector<std::string> chamsvector;
        
        chamsvector.push_back("Lit");
        chamsvector.push_back("Texture");

        
        this->addbutton(rewidth + 12, y + 30, "Chams", &vars.visuals.chams, 0);
        this->addbutton(rewidth + 12 + 170, y + 30, "Hands", &vars.visuals.handchams, 0);
        this->addbutton(rewidth + 12 + 290, y + 30, "Weapons", &vars.visuals.weaponchams, 0);
        
        this->addcombo(rewidth + 12, y + 30, 90, "Players", chamsvector, vars.visuals.playersType, &vars.players_opend, 1);
        this->addcombo(rewidth + 12 + 170, y + 30, 90, "Hands", chamsvector, vars.visuals.handsType, &vars.hands_opend, 1);
        this->addcombo(rewidth + 12 + 290, y + 30, 90, "Weapons", chamsvector, vars.visuals.weaponType, &vars.weapons_opend, 1);
        
    }
    
    if(vars.tabIndex == tTabs::Removals) {
        this->addbutton(rewidth + 12, y + 30, "No Recoil", &vars.misc.norecoil, 0);
        this->addbutton(rewidth + 12, y + 30, "No Visual Recoil", &vars.misc.novisualrecoil, 1);
        this->addbutton(rewidth + 12, y + 30, "Sky Colour", &vars.misc.nosky, 2);
        this->addbutton(rewidth + 12, y + 30, "World Paint", &vars.misc.worldpaint, 3);
    }
    
 if(vars.tabIndex == tTabs::Misc) {
        // Left Side
        this->addbutton(rewidth + 12, y + 30, "Enabled", &vars.misc.enabled, 0);
        this->addbutton(rewidth + 12, y + 30, "Bunny hop", &vars.misc.bhop, 1);
        this->textbox(rewidth + 12, y + 30, 100, "Name", m_szCurrentString, 2, 2, &vars.misc_changename);
        this->textbox(rewidth + 12, y + 30, 100, "Clantag", m_szCurrentString, 3, 3, &vars.misc_clantag);
        this->addslider(rewidth + 12, y + 30, 90, "Field Of View", vars.misc.fov, 4, 60, 0);
        this->addbutton(rewidth + 12, y + 30, "Auto Strafe", &vars.misc.autostrafe, 5);
        this->addbutton(rewidth + 12, y + 30, "Circle Strafe", &vars.misc.circlestrafe, 6);
        this->addbutton(rewidth + 12, y + 30, "Thirdperson (HVH)", &vars.misc.thirdpersonmode, 7);
        // Right Side
        this->addbutton(rewidth + 12 + 170, y + 30, "No AA With Knife", &vars.misc.knifeaa, 0);
        this->addbutton(rewidth + 12 + 170, y + 30, "No Flash", &vars.misc.noflash, 1);
        this->addslider(rewidth + 12 + 170, y + 30, 90, "", vars.misc.flashalpha, 2, 255, 0);

        this->addbutton(rewidth + 12 + 170, y + 30, "Anti Screenshot", &vars.misc.antiscreenshot, 10);
        this->addbutton(rewidth + 12, y + 30, "Anti Untrust", &vars.misc.antiuntrust, 10);
    }
    
    if(vars.tabIndex == tTabs::HvH) {
        std::vector<std::string> antiaim_yaw;
        std::vector<std::string> antiaim_pitch;
        antiaim_yaw.push_back("Off");
        antiaim_yaw.push_back("Backwards");
        antiaim_yaw.push_back("Jitter");
        antiaim_yaw.push_back("FJitter");
        antiaim_yaw.push_back("Slow Spin");
        antiaim_yaw.push_back("Fast Spin");
        antiaim_yaw.push_back("Lower Yaw");
        antiaim_yaw.push_back("Sideways Left");
        antiaim_yaw.push_back("Sideways Right");
        antiaim_yaw.push_back("Custom Fake");
        
        antiaim_pitch.push_back("Off");
        antiaim_pitch.push_back("Emotion");
        antiaim_pitch.push_back("Up");
        if(!vars.misc.antiuntrust) {
            antiaim_pitch.push_back("Lag Down");
            antiaim_pitch.push_back("Fakedown");
            antiaim_pitch.push_back("Custom");
        }
        
        if(vars.misc.aaX == 5)
            this->addslider(rewidth + 12, y +30, 90, "Pitch", vars.misc.customaa, 1, 180, 0);
        
        if(vars.misc.aaY == 9) {
            this->addslider(rewidth + 12 + 170, y +30, 90, "Fake Yaw", vars.misc.fakeyaw, 1, 180, 0);
            this->addslider(rewidth + 12 + 170, y +30, 90, "Real Yaw", vars.misc.realyaw, 2, 180, 0);
        }
        
        this->addcombo(rewidth + 12, y + 30, 90, "Anti Aim X", antiaim_pitch, vars.misc.aaX, &vars.aaX_opend, 0);
        
        this->addcombo(rewidth + 12 + 170, y + 30, 90, "Anti Aim Y", antiaim_yaw, vars.misc.aaY, &vars.aaY_opend, 0);
        
        this->addbutton(rewidth + 12, y + 30, "At Targets", &vars.misc.attargets, 6);
        this->addbutton(rewidth + 12, y + 30, "Fake", &vars.misc.fakeaa, 7);
        
        
    }
    
    if(vars.tabIndex == tTabs::Playerlist) {
        if(!bCheckState()) {
            this->drawstringINDEX(rewidth + 12, y + 30, Color(0, 0, 0, 255), "Player is not ingame.", 0, false, IFlags::IFLAG_DANGER);
        } else {
            // to do, make a player list : ) - ViKiNG NOTE.
            //this->drawstringINDEX(rewidth + 12, y + 30, Color(0, 0, 0, 255), "Player is ingame but there are no players to be found.", 0, false, IFlags::IFLAG_INFO);
            std::vector<std::string> PitchResolver, YawResolver;
        
            PitchResolver.push_back("Auto");
            PitchResolver.push_back("Down");
            PitchResolver.push_back("Up");
            
            YawResolver.push_back("Auto");
            YawResolver.push_back("Half Left");
            YawResolver.push_back("Half Right");
            YawResolver.push_back("Jitter");
            YawResolver.push_back("Spin");
            YawResolver.push_back("Lower Body");
            YawResolver.push_back("45 Step");
            
            int bPadding = 0;
            char plinfo[255];
            auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
            for(int i = 1; i < 64; i++) {
                auto* entity = pEntList->GetClientEntity(i);
                
                if(!entity)
                    continue;
                
                if(entity == local)
                    continue;
                
                if(entity->GetTeam() == local->GetTeam())
                    continue;
                
                if(entity->GetTeam() != 2 && entity->GetTeam() != 3)
                    continue;
                
                
                
                player_info_t info;
                pEngine->GetPlayerInfo(i, &info);
                
                IFlags flag;
                
                if(entity->GetTeam() == 2)
                    flag = IFlags::IFLAG_DANGER;
                else if(entity->GetTeam() == 3)
                    flag = IFlags::IFLAG_INFO;
            
                
                this->addplayerlistbutton(rewidth + 12, y + 30, 90, 20, bPadding, vars.playerTab, info.name, flag);
                
                if(bPadding == vars.playerTab) {
                    sprintf(plinfo, "Player info for : %s with index %i", info.name, entity->GetIndex());
                    this->drawstringINDEX(rewidth + 12 + 170, y + 30, Color(0, 0, 0, 255), plinfo, 0, false, flag);
                    this->addbutton(rewidth + 12 + 170, y + 30, "Resolve", &gCorrections[entity->GetIndex()].resolved, 1);
                    this->addbutton(rewidth + 12 + 170, y + 30, "Whitelist", &gCorrections[entity->GetIndex()].whitelist, 2);
                    this->addcombo(rewidth + 12 + 170, y + 30, 90, "Pitch", PitchResolver, gCorrections[entity->GetIndex()].dropdown_x, &vars.playerlist_opend_x[entity->GetIndex()], 3);
                    this->addcombo(rewidth + 12 + 170 + 150, y + 30, 90, "Yaw", YawResolver, gCorrections[entity->GetIndex()].dropdown_y, &vars.playerlist_opend_y[entity->GetIndex()], 3);
                }
                bPadding++;
            }
        }
    }
    
    if(vars.tabIndex == tTabs::Colors) {
        std::vector<std::string> ColorTabs;
        
        ColorTabs.push_back("CT Chams");
        ColorTabs.push_back("T Chams");
        ColorTabs.push_back("CT Box");
        ColorTabs.push_back("T Box");
        ColorTabs.push_back("Hands");
        ColorTabs.push_back("Weapons");
        ColorTabs.push_back("World");
        
        for(int i = 0; i < ColorTabs.size(); i++) {
            this->drawpalettetabs(rewidth, y + 40, w, ColorTabs[i].c_str(), vars.colors.tab, i, ColorTabs.size());
        }
        
        if(vars.colors.tab == cColorTabs::CTChams) {
            this->drawcolorpicker(rewidth + 12, y + 70, "CT Chams", vars.colors.ctchams, 0);
            
            this->drawcolorpicker(rewidth + 12 + 300, y + 70, "CT Chams Ignore", vars.colors.ctchams_ign, 0);
        }
        
        if(vars.colors.tab == cColorTabs::TChams) {
            this->drawcolorpicker(rewidth + 12, y + 70, "T Chams", vars.colors.tchams, 0);
            
            this->drawcolorpicker(rewidth + 12 + 300, y + 70, "T Chams Ignore", vars.colors.tchams_ign, 0);
        }
        
        if(vars.colors.tab == cColorTabs::CTBoxes) {
            this->drawcolorpicker(rewidth + 12, y + 70, "CT Box", vars.colors.ctbox, 0);
            
            this->drawcolorpicker(rewidth + 12 + 300, y + 70, "CT Box Wall", vars.colors.ctbox_ign, 0);
        }
        
        if(vars.colors.tab == cColorTabs::TBoxes) {
            this->drawcolorpicker(rewidth + 12, y + 70, "T Box", vars.colors.tbox, 0);
            
            this->drawcolorpicker(rewidth + 12 + 300, y + 70, "T Box Wall", vars.colors.tbox_ign, 0);
        }
        
        if(vars.colors.tab == cColorTabs::HANDChams) {
            this->drawcolorpicker(rewidth + 12, y + 70, "Hands", vars.colors.hands, 0);
            
            this->drawcolorpicker(rewidth + 12 + 300, y + 70, "Hands Ignore", vars.colors.hands_ign, 0);
        }
        
        if(vars.colors.tab == cColorTabs::WEAPCHams) {
            this->drawcolorpicker(rewidth + 12, y + 70, "Weapon", vars.colors.weapon, 0);
            
            this->drawcolorpicker(rewidth + 12 + 300, y + 70, "Weapon Ingore", vars.colors.weapon_ign, 0);
        }
        
        if(vars.colors.tab == cColorTabs::World) {
            this->drawcolorpicker(rewidth + 12, y + 70, "World", vars.colors.world, 0);
            
            this->drawcolorpicker(rewidth + 12 + 300, y + 70, "Sky Colour", vars.colors.Sky, 0);

        }
    }
    
    this->MoveMenu(rewidth, y, w, hh, 0);
    
    WasPressed(MOUSE_LEFT);
}
