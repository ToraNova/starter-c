/*
 * template for starting writing pam
 * references:
 * https://github.com/fedetask/pam-tutorials/blob/master/pam-module/src/main.c
 * man pam_sm_<functions>
 *
 * modified by toranova
 * mailto: chia_jason96@live.com
 */
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <security/pam_appl.h>
#include <security/pam_ext.h>
#include <security/pam_modules.h>
#include <security/pam_modutil.h>

/*
 * defined in pwd.h
 * struct passwd {
 *                char   *pw_name;       // username
 *                char   *pw_passwd;     // user password
 *                uid_t   pw_uid;        // user ID
 *                gid_t   pw_gid;        // group ID
 *                char   *pw_gecos;      // user information
 *                char   *pw_dir;        // home directory
 *                char   *pw_shell;      // shell program
 * };
*/

// PAM entry point for authentication verification (ensure user is who they claim they are)
int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	// TODO: handle authentication code here
	// flags: PAM_SILENT, PAM_DISALLOW_NULL_AUTHTOK
	char *user = NULL; //variable to store username
	int rc;

	// get username, 3rd arg is prompt "login:" (default).
	rc = pam_get_user(pamh, (const char **) &user, NULL);
	if (rc != PAM_SUCCESS || user == NULL) {
		// username error
		return PAM_USER_UNKNOWN;
	}

	// allow actual linux-users to authenticate only (they exist in /etc/passwd)
#if 0
	uid_t euid; // program effective uid
	struct passwd *pdat; // /etc/passwd data struct
	// get passwd struct from /etc/passwd corresponding to username
	pdat = pam_modutil_getpwnam(pamh, user);
	if (pdat == NULL) {
		// no pwd data in /etc/passwd (probably not a valid linux user)
		return PAM_USER_UNKNOWN;
	}

	// get and store euid of the runner
	euid = geteuid();
	if(getuid() != euid || euid == 0 ){
		rc = seteuid(pdat->pw_uid); //drop privilege to user's privilege
		if (!rc){
			perror("seteuid");
			return PAM_AUTH_ERR;
		}
		//rmb to reset euid back to original 'euid'
	}
#endif

	//TODO: authentication here
	// password based
	char *token = NULL; //user to supply token
	rc = pam_get_authtok(pamh, PAM_AUTHTOK, (const char **) &token, "token:");
	if(rc != PAM_SUCCESS) {
		// error getting auth token
		return PAM_AUTH_ERR;
	}

	// requires password (no null accepted)
	if( flags & PAM_DISALLOW_NULL_AUTHTOK && (token == NULL || strcmp(token, "") == 0)) {
		return PAM_AUTH_ERR;
	}

	// WARNING: THIS IS AN EXAMPLE ONLY! DO NOT USE THIS IN PRACTICE!
	// effectively, EVERY user will need to share the same password for this example
	// you should implement your own password management system, or don't even use passwords
	// at all!
	const char *hardpass = "danger"; //hardcoded password
	if( strcmp(token, hardpass) ){
		//password supplied by user (token) and required password (hardpass) differs
		return PAM_AUTH_ERR;
	}

	// see /usr/include/security/_pam_types.h for a list of return codes.
	return PAM_SUCCESS; //return this if and only if you are sure the user valid and present.
}

// PAM entry point for accounting (ensure user has the authority to do something
int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	// TODO: handle access control code here
	// flags: PAM_SILENT, PAM_DISALLOW_NULL_AUTHTOK
	char *user = NULL;

	// arbitrary security access controls.
	// in this example:
	// only user named 'cjason' can login
	// account 'expired' is expired (you should obviously implement your own expiry check)
	pam_get_item(pamh, PAM_USER, (const void **)&user); //get user name from PAM
	if (strcmp(user, "cjason") == 0){
		// ok
		return PAM_SUCCESS;
	}else if(strcmp(user, "expired") == 0){
		// account expired
		return PAM_ACCT_EXPIRED;
	}else{
		return PAM_PERM_DENIED;
	}
}

// PAM entry point for session creation
int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	//TODO: handle session start
	//code runs when app calls pam_open_session
	// flags: PAM_SILENT
	return PAM_IGNORE;
}

// PAM entry point for session cleanup
int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	//TODO: handle session close
	//code runs when app calls pam_close_session
	// flags: PAM_SILENT
	return PAM_IGNORE;
}

// PAM entry point for setting user credentials (that is, to actually
// establish the authenticated user's credentials to the service provider)
// this runs BEFORE session opens, see man pam_setcred
int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	// TODO: handle credential change
	// user has been authenticated, and would like to change their credentials
	// flags:
	// PAM_SILENT, PAM_ESTABLISH_CRED, PAM_DELETE_CRED, PAM_REINITIALIZE_CRED, PAM_REFRESH_CRED
	return PAM_IGNORE;
}

// PAM entry point for authentication token (password) changes
int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	// TODO: handle (re-)set of the authentication token of the user
	// flags:
	// PAM_SILENT, PAM_CHANGE_EXPIRED_AUTHTOK, PAM_PRELIM_CHECK, PAM_UPDATE_AUTHTOK
	return PAM_IGNORE;
}
