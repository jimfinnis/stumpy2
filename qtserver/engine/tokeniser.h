#ifndef __TOKENISER_H
#define __TOKENISER_H

#include <stdio.h>
#include <string.h>

/**
 * @file
 * The Tokeniser and associated classes, which split a line
 * of input into tokens such as keywords, strings, numbers and
 * identifiers.
 */

struct TokenRegistry
{
    const char *word;
    int token;
};

/// should be a union, really..
struct Token
{
    char s[1024];
    float f;
    int i;
};

/// an interface for a error handler (see seterrorhandler())
class ITokeniserErrorHandler
{
public:
    virtual void HandleTokeniserError(class Tokeniser *t) = 0;
};

class Tokeniser
{
public:    
    
    /// this object gets called when the error gets set.
    void seterrorhandler(ITokeniserErrorHandler *h)
    {
        handler = h;
    }
    
    /// initialise
    void init();
    
    /// set the token table
    void settokens(TokenRegistry *k);
    
    
    /// start tokenising a new string.
    /// Takes start and char after end of string (if null, will use strlen())
    void reset(const char *buf,const char *_end=NULL);
    
    /// move onto next token, returning its type.
    int getnext();
    
    /// move onto next token and ensure it is the given token
    bool getnextcheck(int ensure){
        int t = getnext();
        if(t!=ensure){
            seterror();
            return false;
        }
        return true;
    }
            
    
    /// return the current token type
    int getcurrent()
    {
        return curtype;
    }
    
    /// return the error state, which is set when a getnext..() has hit something of the wrong type
    bool iserror() { return error; }
    
    /// get the current token as a raw token
    Token gettoken()
    {
        return val;
    }
    
    /// rewind to the previous token. Can only be done once.
    void rewind();
    
    /// get the value of the next token - must be a float or int
    float getfloat()
    {
        if(curtype==floattoken)
            return val.f;
        else if(curtype==inttoken)
            return (float)val.i;
        else
            return -9999;
    }
    /// get the value of the next token - must be a float or int
    int getint()
    {
        if(curtype==inttoken)
            return val.i;
        else if(curtype==floattoken)
            return (int)val.f;
        else
            return -9999;
    }
    
    /// get the string value of the next token
    char *getstring()
    {
        return val.s;
    }
    
    /// get the char value of the next token
    char getcharacter()
    {
        return val.s[0];
    }
    
    /// get the next item, ensure it's a number, and return it or -9999. If fails, sets the error state.
    float getnextfloat()
    {
        int t = getnext();
        if(t!=floattoken && t!=inttoken){seterror();return -9999;}
        return getfloat();
    }
    /// get the next item, ensure it's a number, and return it or -9999. If fails, sets the error state.
    int getnextint()
    {
        int t = getnext();
        if(t!=floattoken && t!=inttoken){seterror();return -9999;}
        return getint();
    }
    
    /// get the next delimited string, or return false on error
    bool getnextstring(char *out);
    
    /// get the next identifier, or return false on error
    bool getnextident(char *out);
    
    /// return the rest of the line as a string, bypassing the tokeniser
    const char *restofline();
    
    /// skip ahead to a given character. Being a low level routine, this takes a character code - not
    /// a token!
    void skipahead(char c);
    
    /// get currnet line number
    int getline()
    {
        return line;
    }
    
    /// turn on debugging
    void settrace(bool t)
    {
        trace = t;
    }
    
    /// if this sequence of characters is reached, skip forwards to the end of the line
    void setcommentlinesequence(const char *s)
    {
        commentlinesequence=s;
        if(s)
            commentlinesequencelen=(int)strlen(s);
        else
            commentlinesequencelen=0;
    }
    
    /// return the index of the character within the stream
    int getpos() {
        return current-start;
    }
    
    const char *getbuf(){
        return start;
    }
    
private:
    void dprintf(const char *s,...);
    
    /// find the token for a keyword if one exists
    int findkeyword(const char *s);
    
    /// skip whitespace
    const char *skipspace(const char *p);
    
    /// set the errorcode and call the handler
    void seterror()
    {
        error = true;
        if(handler)handler->HandleTokeniserError(this);
    }
    
    const char *start;
    const char *current;
    const char *end;
    int curtype;
    int chartable[128];
    const char *commentlinesequence;
    int commentlinesequencelen;
    bool error;
    
    int line;
    bool trace;
    
    Token val;
    TokenRegistry *tokens;
    
    int endtoken,inttoken,stringtoken,identtoken,floattoken;
    ITokeniserErrorHandler *handler;
    
    Token prevval;
    const char *previous;
    int prevtype;
    int prevline;
    
};

/// used for parsing errors (sometimes!)
#include "serverbase/util/exception.h"

class ParseException : public Exception {
protected:
    int line;
public:
    ParseException(Tokeniser *t,const char *err=NULL):
    Exception(err){
        line = t->getline();
    }
    
    /// return the error string
    virtual const char *what () const throw (){
        static char buf[1024];
        snprintf(buf,1024,"Line %d : %s\n",line,error);
        return buf;
    }
};

/// used for parsing errors (sometimes!)
class UnexpException : public ParseException {
public:
    UnexpException(Tokeniser *t,const char *exp=NULL):
    ParseException(t,NULL){
        if(exp){
            snprintf(error,512,"Unexpected '%s' expected %s",
                     t->getstring(),exp);
        } else {
            snprintf(error,512,"Unexpected '%s'",
                     t->getstring());
        }
    }
};



#endif /* __TOKENISER_H */
