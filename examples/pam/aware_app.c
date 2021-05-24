/*
 * a simple PAM application
 * PAM - pluggable authentication modules
 * a method of unifying authentication, account, sessions and password controls.
 * https://web.archive.org/web/20190420073246/https://fedetask.com/writing-a-linux-pam-aware-application/
 * requires a configuration file in /etc/pam.d/<pamc>
 * auth        required        <pam_name>.so
 * account     required        <pam_name>.so
 * password    required        <pam_name>.so
 * session     required        <pam_name>.so
 *
 * <pam_name> is any pam that is installed under /usr/lib/security
 * (i.e., pam_unix);
 *
 * this example mainly is on auth/account only. please find additional info on password/session.
 *
 * toranova, May 19 2021
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
	pam_handle_t *pamh = NULL;
	const char *pamc = "pam_example"; //config name under /etc/pam.d
	int rc;
	char *user;

	rc = pam_start(pamc, NULL, &conv, &pamh);
	if (rc != PAM_SUCCESS){
		fprintf(stderr, "failure in pam initialization: %s\n", pam_strerror(pamh, rc));
		return -1;
	}

	rc = pam_authenticate(pamh, 0); // do authentication (user will be asked for user and password)
	if (rc != PAM_SUCCESS) {
		fprintf(stderr, "failure in pam authentication: %s\n", pam_strerror(pamh, rc));
		return -1;
	}

	rc = pam_get_item(pamh, PAM_USER, (const void **)&user);
	if (rc != PAM_SUCCESS || user == NULL){
		fprintf(stderr, "failure to get user: %s\n", pam_strerror(pamh, rc));
		return -1;
	}
	printf("pam auth %s ok.\n", user);

	rc = pam_acct_mgmt(pamh, 0); // do account management (check the account can access the system)
	if (rc != PAM_SUCCESS) {
		fprintf(stderr, "failure in pam account management: %s\n", pam_strerror(pamh, rc));
		return -1;
	}
	printf("pam account %s ok.\n", user);

	// password changing
#if 0
	printf("do you want to change your password? (answer y/n): ");
	char answer = getc(stdin); // get user answer
	if (answer == 'y') {
		rc = pam_chauthtok(pamh, 0); // do update (user will be asked for current and new password) */
		if (rc != PAM_SUCCESS) {
			fprintf(stderr, "failure in pam password: %s\n", pam_strerror(pamh, rc));
			return 1;
		}
	}
#endif

	pam_end(pamh, rc); // ALWAYS terminate the pam transaction!
	return 0;
}
