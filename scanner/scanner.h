

#ifndef SCANNER_H
#define SCANNER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

enum ScannerContextType 
{
    StringHandle
    // File
    // Stream?
};

struct ScannerContext 
{
    int Length;
    int Index;

    ScannerContextType Type;

    // Generic Storage for whatever information is required for the given
    // Type (String, would mean Handle is a c-string; File, would mean Handle
    // is a FILE handle etc...)
    void * Handle;
};

ScannerContext * scanner_init_string(char * contents) 
{
    auto result = (ScannerContext *)malloc(sizeof(ScannerContext));
    result->Index = -1;
    result->Length = strlen(contents);
    result->Type = StringHandle;
    result->Handle = contents;
    return result;
}

ScannerContext * scanner_dispose_string(ScannerContext * context) 
{
    if (context != NULL) 
    {
        free(context);
    }

    return NULL;
}

bool scanner_is_eof(ScannerContext* context) 
{
    return context->Index >= context->Length;
}

char scanner_peek(ScannerContext* context) 
{
    // TODO(jwwishart) we don't really test this 
    if (context->Index == -1) {
        context->Index++;
    }

    // c-string - simple so just cast and return the char
    if (context->Type == StringHandle) 
    {
        return ((char *)context->Handle)[context->Index];
    }

    return '\0';
};

char scanner_move_next(ScannerContext* context) 
{
    if (scanner_is_eof(context)) 
    {
        return '\0';
    }

    if (context->Index + 1 >= context->Length) 
    {
        return '\0';
    }

    context->Index++;
    return scanner_peek(context);
}


#ifdef __cplusplus
}
#endif

#endif /* SCANNER_H */