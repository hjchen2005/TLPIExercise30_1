/*
 * Implement setenv() and unsetenv() using getenv(), putenv(), and, where
 * necessary, code that directly modifies environ.  Your version of
 * unsetenv() should check to see whether there are multiple definitions
 * of an environment variable, and remove them all (which is what the
 * glibc version of unsetenv() does).
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>

extern char **environ;

int setenv(const char *envname, const char *envval, int overwrite)
{
	char *pNewEnvEntry;
	char **ppEnvEntry;

	/* validate the input */
	if (envname == NULL || envname[0] == '\0') {
		errno = EINVAL;
		return -1;
	}
	if (strchr(envname, '=') != NULL) {
		errno = EINVAL;
		return -1;
	}

	/* search for any existing entry with envname */
	for (ppEnvEntry = environ; *ppEnvEntry != NULL; ppEnvEntry++) {
		/* looking for '{envname}=' */
		if (strncmp(*ppEnvEntry, envname, strlen(envname)) == 0 &&
		    *ppEnvEntry[strlen(envname)] == '=') {
			if (overwrite == 0)
				return 0; /* we are done here */
			break; /* we found our entry */
		}
	}

	/* 
	 * add an entry and set pEnvEntry, the size of
	 * which fits {envname}={envval}\0.  Set environ to point
	 * to this new memory location and ensure next entry is NULL
	 * so we can continue to treat it as a list.
	 */
	pNewEnvEntry  = malloc(strlen(envname) + strlen(envval) + 2);
	sprintf(pNewEnvEntry, "%s=%s", envname, envval);
	ppEnvEntry = pNewEnvEntry;
	(ppEnvEntry) = NULL;
	return 0;
}

/*
 * DESCRIPTION
 * 
 * The unsetenv() function shall remove an environment variable from the
 * environment of the calling process. The name argument points to a
 * string, which is the name of the variable to be removed. The named
 * argument shall not contain an '=' character. If the named variable
 * does not exist in the current environment, the environment shall be
 * unchanged and the function is considered to have completed
 * successfully.
 * 
 * If the application modifies environ or the pointers to which
 * it points, the behavior of unsetenv() is undefined. The
 * unsetenv() function shall update the list of pointers to which
 * environ points.
 * 
 * The unsetenv() function need not be reentrant. A function that
 * is not required to be reentrant is not required to be
 * thread-safe.
 * 
 * RETURN VALUE
 * 
 * Upon successful completion, zero shall be returned. Otherwise,
 * -1 shall be returned, errno set to indicate the error, and the
 * environment shall be unchanged.
 * 
 * ERRORS
 * 
 * The unsetenv() function shall fail if:
 * 
 * [EINVAL] The name argument is a null pointer, points to an empty
 * string, or points to a string containing an '=' character.
 * 
 */
int unsetenv(const char *name)
{
	char **ppEntryToMove;
	char **ppTargetLocation;

	/* validate the input */
	if (name == NULL || name[0] == '\0') {
		errno = EINVAL;
		return -1;
	}
	if (strchr(name, '=') != NULL) {
		errno = EINVAL;
		return -1;
	}

	/* search for any existing entry with name */
	for (ppTargetLocation = environ; *ppTargetLocation != NULL; ppTargetLocation++) {
		/* looking for '{name}=' */
		if (strncmp(*ppTargetLocation, name, strlen(name)) == 0 &&
		    *ppTargetLocation[strlen(name)] == '=') {
			break; /* we found our entry */
		}
	}
	
	if (ppTargetLocation == NULL) {
		return 0; /* not found, consider done */
	} else if (*(ppTargetLocation + 1) == NULL) {
		ppTargetLocation = NULL;
	} else {
		/* 
		 * in this case, we need to do some shuffling.  The easiest is
		 * to find the last entry in the list and move that to this
		 * spot, setting that entry to NULL.  We are still maintaining
		 * linear time operation
		 */
		ppEntryToMove = ppTargetLocation;
		while (*(++ppEntryToMove + 1) != NULL);
		ppTargetLocation = ppEntryToMove;
		ppEntryToMove = NULL;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	
	return 0;
}
