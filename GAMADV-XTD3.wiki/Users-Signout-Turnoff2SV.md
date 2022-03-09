# Users - Signout and Turn off 2-Step Verification
- [API documentation](#api-documentation)
- [Collections of Users](Collections-of-Users)
- [Signout Users](#signout-users)
- [Turn off 2-Step Verification](#turn-off-2-step-verification)

## API documentation
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/users/signOut
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/twoStepVerification/turnOff

## Signout Users
Sign a user out of all web and device sessions and reset their sign-in cookies.
The user will have to sign in by authenticating again.
```
gam <UserTypeEntity> signout
```
## Turn off 2-Step Verification
Turn off 2-Step Verification for a user.
If successful this call will turn off 2-Step Verification and also remove all registered second steps on the user account.
This call will fail if the user is not enrolled in 2-Step Verificationin or has 2-Step Verification enforced, or is enrolled in the Advanced Protection Program.
```
gam <UserTypeEntity> turnoff2sv
```
