/**
 * @file
 * Error strings - see errors.h and Server::fail / Server::success
 *
 * 
 * 
 */

/// the error strings, indexed by macros in errors.h
const char *errorStrings[] = {
    "OK",
    "Unknown command",
    "Bad number of arguments",
    "Entity already exists",
    "No such entity",
    "No such component type",
    "Input index out of range",
    "No such patch",
    "No such component",
    "Link of uninitialised component",
    "Output index out of range",
    "Type mismatch in link",
    "Bad parameter type",
    "Parameter value out of range",
    "Parameter ID out of range",
    
    "Enum ID out of range",
    "Too many parameters in type",
    "??","??","??","??",
};
