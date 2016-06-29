/**
 * @file
 * List of error definitions which are sent back to the client;
 * errors.cpp has the strings in errorStrings[].
 *
 * 
 * 
 */

#ifndef __ERRORS_H
#define __ERRORS_H

extern const char *errorStrings[];

/// the non-error error, everything went OK
#define SE_OK		0

/// the client used an unknown command
#define SE_UNKNOWNCOMMAND 1

/// each command has a fixed number of arguments - the client gave the wrong number
#define SE_BADARGC        2

/// the client asked to create an entity which already exists
#define SE_ALREADY	3

/// the client referred to an entity which doesn't exist
#define SE_NOSUCH	4

/// the client tried to create a component of an unknown type
#define SE_NOSUCHCOMPT	5

/// the input number specified is out of range
#define SE_INPUTRANGE 6

/// the client specified an unknown patch
#define SE_NOSUCHPATCH 7

/// the client specified an unknown component
#define SE_NOSUCHCOMP 8

/// the client asked to link an uninitialised component to another component (internal error)
#define SE_LINKUNINIT 9

/// the output number specified is out of range
#define SE_OUTPUTRANGE 10

/// the client asked to link an output to an input of a different type
#define SE_LINKMISMATCH 11

/// the client sent a parameter change with a code character which was not
/// the same as the code character for that parameter's type
#define SE_BADPARAMTYPE 12

/// client tried to set parameter value out of range
#define SE_PARAMOUTOFRANGE 13

/// parameter ID out of range in parameter set
#define SE_NOSUCHPARAM 14

/// enumeration out of range
#define SE_ENUMOUTOFRANGE 15

/// too many params
#define SE_TOOMANYPARAMS 16

/// unknown connection type in search by ID
#define SE_UNKNOWNCONTYPE 17

#endif /* __ERRORS_H */
