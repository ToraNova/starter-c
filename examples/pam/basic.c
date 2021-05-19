/*
 * a simple PAM application
 * PAM - pluggable authentication modules
 * a method of unifying authentication, account, sessions and password controls.
 * https://web.archive.org/web/20190420073246/https://fedetask.com/writing-a-linux-pam-aware-application/
 * requires a configuration file in /etc/pam.d/pam_example
 * auth        required        pam_unix.so
 * account     required        pam_unix.so
 * password    required        pam_unix.so
 *
 * toranova, May 19 2021
 *
 * compile with:
 * gcc -o run main.c -lpam -lpam_misc
 */

#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdlib.h>

static struct pam_conv conv = {
	misc_conv, // Conversation function defined in pam_misc.h
	NULL // We don't need additional data now
};

int main() {
	pam_handle_t *handle = NULL;
	const char *service_name = "pam_example";
	int retval;
	char *username;

	retval = pam_start(service_name, NULL, &conv, &handle);
	if (retval != PAM_SUCCESS){
		fprintf(stderr, "failure in pam initialization: %s\n", pam_strerror(handle, retval));
		return 1;
	}

	retval = pam_authenticate(handle, 0); // do authentication (user will be asked for username and password)
	if (retval != PAM_SUCCESS) {
		fprintf(stderr, "failure in pam authentication: %s\n", pam_strerror(handle, retval));
		return 1;
	}

	retval = pam_acct_mgmt(handle, 0); // do account management (check the account can access the system)
	if (retval != PAM_SUCCESS) {
		fprintf(stderr, "failure in pam account management: %s\n", pam_strerror(handle, retval));
		return 1;
	}

	pam_get_item(handle, PAM_USER, (const void **)&username);
	printf("welcome, %s\n", username);

	printf("do you want to change your password? (answer y/n): ");
	char answer = getc(stdin); // get user answer
	if (answer == 'y') {
		retval = pam_chauthtok(handle, 0); // do update (user will be asked for current and new password) */
		if (retval != PAM_SUCCESS) {
			fprintf(stderr, "failure in pam password: %s\n", pam_strerror(handle, retval));
			return 1;
		}
	}

	pam_end(handle, retval); // ALWAYS terminate the pam transaction!
}
