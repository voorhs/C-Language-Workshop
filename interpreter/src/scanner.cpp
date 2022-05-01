#include "scanner.h"

#define NAME_LEN 3

VecOfIdent Scanner::TID;

id_lex::id_lex(std::string word):
    Lex(LEX_ID)
{
    name = word;
}

std::string id_lex::get_string() const
{
    return name;
}

int id_lex::get_int() const
{
    return Scanner::TID.find(name);
}

Scanner::Scanner(const char* fileName) {
    if (!(fp = fopen(fileName, "r")))
        throw  "can't open file";
}

std::ostream& operator<<(std::ostream& out, Lex* l)
{    
    int type = l->get_type(),
        shift = l->get_index();
    out << '\t' << type << '\t';

    if (typeid(*l) == typeid(keyWord_lex))
        out << "\t(TW)\t\t" << Lex::TW[shift] << '\t';

    else if (typeid(*l) == typeid(delimiter_lex))
        out << "\t(TD)\t\t" << Lex::TD[shift] << '\t';

    else if (typeid(*l) == typeid(literal_lex))
    {
        if (type == LEX_INT_LITER)
            out << "\tint literal\t"       << l->get_int();
        
        else if (type == LEX_STRING_LITER)
            out << "\tstring literal\t"    << l->get_string();
        
        else if (type == LEX_BOOL_LITER)
            out << "\tbool literal\t"      << (l->get_bool() ? "true" : "false");
    }
    else if (typeid(*l) == typeid(id_lex))
    {
        int index = Scanner::TID.find(l->get_string());        
        
        out << "\t(TID)\t\t" << l->get_string() << ' ' << index;
    }
    else if (typeid(*l) == typeid(RPN_lex))
    {
        out << "\tRPN\t";
        
        if (type == POLIZ_ADDRESS)
            out << "\tadress\t" << l->get_int();
        
        else if (type == POLIZ_LABEL)
            out << "\tlabel\t" << l->get_int();
        
        else if (type == POLIZ_GO)
            out << "\tGO\t";
        
        else if (type == POLIZ_FGO)
            out << "\tFGO\t";
    }
    return out;
}

void Scanner::addID(std::string name) {
    Ident id;
    id.set_name(name);
    TID.push_back(id);
}

Lex* Scanner::get_lex()
{
    enum state { H, IDENT, NUMB, STR, SLASH, COM, ALE, PLUS, MINUS, NEQ }; // set of states
    
    state CS = H;   // initial current state

    unsigned int number;    // to scan numbers
    signed int sign = 1;
    std::string word;       // to scan the rest

    while (true)
    {
        char c = fgetc(fp);
        switch (CS)
        {
            case H:
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
                    {}                                                  // skip blank characters
                else if (isalpha(c)) {
                    word += c;
                    CS = IDENT;
                }
                else if (isdigit(c)) {
                    number = c - '0';
                    CS = NUMB;
                }
                else if (c == '"') {
                    CS = STR;
                }
                else if (c == '/') {
                    CS = SLASH;
                }
                else if (c == '=' || c == '<' || c == '>') {
                    word += c;
                    CS = ALE;
                }
                else if (c == '+') {
                    word += c;
                    CS = PLUS;
                }
                else if (c == '-') {
                    word += c;
                    CS = MINUS;
                }
                else if (c == '!') {
                    word += c;
                    CS = NEQ;
                }
                else if (c == EOF) {
                    return new Lex(LEX_FIN);
                }
                else
                {
                    word += c;

                    int index = Lex::TD.find(word);      // might be delimiter

                    if (!index)
                        throw c;
                    else
                        return new delimiter_lex(index);
                }
                break;

            case IDENT:
                if (isalpha(c) || isdigit(c))
                    word += c;
                
                else
                {
                    ungetc(c, fp);

                    int index = Lex::TW.find(word);
                    if (!index)
                    {
                        index = TID.find(word);
                        if (!index)
                            addID(word);            // already declared ID
                                    
                        return new id_lex(word);         // new ID
                    }
                    
                    bool isTrue  = (word == "true"),
                         isFalse = (word == "false");
                    
                    if (isTrue || isFalse)
                        return new literal_lex(!isFalse || isTrue);                    

                    return new keyWord_lex(index);                     // key word
                }
                break;

            case NUMB:
                if (isdigit(c))
                    number = number * 10 + (c - '0');
                
                else
                {
                    ungetc(c, fp);       
                    int res = number * sign;             
                    return new literal_lex(res);             // INT_LITER
                }
                break;

            case STR:
                if (c == '"') {
                    return new literal_lex(word);         // STRING_LITER
                }
                else if (c == EOF) {
                    throw "unexpected EOF";
                }
                else {
                    word += c;
                }
                break;

            case SLASH:
                if (c == '*')
                    CS = COM;
                
                else    // division sign  
                {
                    ungetc(c, fp);                    
                                                            
                    return new delimiter_lex(LEX_SLASH);
                }
                break;

            case COM:
                if (c == '*')
                {
                    c = getchar();
                    if (c == '/')
                        CS = H;         /// ?????? should we do unget(c, fp) ??????
                }
                else if (c == EOF)
                    throw "unexpected EOF";
                
                break;

            case ALE:
                if (c == '=')
                {
                    word += c;
                    
                    return new delimiter_lex(Lex::TD.find(word));
                }
                else
                {
                    ungetc(c, fp);
                    
                    return new delimiter_lex(Lex::TD.find(word));
                }
                break;

            case PLUS:
                if (isdigit(c))
                {
                    number = c - '0';
                    CS = NUMB;                  /// should we return '+' lexeme?
                }
                else
                {
                    ungetc(c, fp);
                                        
                    return new delimiter_lex(LEX_PLUS);
                }
                break;

            case MINUS:
                if (isdigit(c))
                {
                    number = (c - '0');
                    sign = -1;
                    CS = NUMB;
                }
                else
                {
                    ungetc(c, fp);
                                        
                    return new delimiter_lex(LEX_MINUS);
                }
                break;

            case NEQ:
                if (c == '=')
                {                                        
                    return new delimiter_lex(LEX_NEQ);
                }
                else
                    throw "unexpected character after '!' character: " + c;
                
                break;
        }
    } while (true);
}