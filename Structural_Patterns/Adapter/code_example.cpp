// ===== Violation Example =====
// Directly using a third-party login API (incompatible interface)

#include <iostream>
#include <string>
using namespace std;

// This is the interface your app expects:
class IAuthProvider {
public:
    virtual bool login(const string& username, const string& password) = 0;
    virtual ~IAuthProvider() = default;
};

// Your code expects to call login(username, password).

// Third-party API (incompatible interface):
class GoogleLoginAPI {
public:
    // The method is completely different; expects a Google token.
    bool googleSignIn(const string& oauthToken) {
        cout << "[GoogleLoginAPI] Signing in with token: " << oauthToken << endl;
        return !oauthToken.empty();
    }
};

// Client code attempts to use the GoogleLoginAPI directly:
void authenticateUser(const string& username, const string& password) {
    // You want to use Google, but your API expects username/password,
    // while Google wants an OAuth token.
    GoogleLoginAPI googleApi;
    // There is no way to call googleApi.googleSignIn() with username/password!
    cout << "Cannot authenticate: Incompatible interface!\n";
}

int main() {
    authenticateUser("alice@gmail.com", "password123");
    return 0;
}

/*
Output:
Cannot authenticate: Incompatible interface!
*/
// Problem: Client code can't work with GoogleLoginAPI as expected, since interfaces don't match.


// ===== Adapter Pattern-Compliant Example =====

#include <iostream>
#include <string>
using namespace std;

// Target interface (what the app expects)
class IAuthProvider {
public:
    virtual bool login(const string& username, const string& password) = 0;
    virtual ~IAuthProvider() = default;
};

// Adaptee (third-party API, unchanged)
class GoogleLoginAPI {
public:
    bool googleSignIn(const string& oauthToken) {
        cout << "[GoogleLoginAPI] Signing in with token: " << oauthToken << endl;
        return !oauthToken.empty();
    }
};

// Adapter: Translates your interface to the third-party API
class GoogleAdapter : public IAuthProvider {
    GoogleLoginAPI googleApi;
public:
    bool login(const string& username, const string& password) override {
        // Normally you'd convert username/password to an OAuth token here.
        // For demo, we'll just concatenate them as a mock "token."
        string oauthToken = username + ":" + password;
        return googleApi.googleSignIn(oauthToken);
    }
};

//Adaptee 2
class XLoginAPI{
    public:
        bool XSignIn(const string &secretToken){
            cout<<"[TwitterLoginAPI] Signing In with secretToken : " << secretToken << endl;
            return !secretToken.empty();
        }
};

//Adpater : For X
class XAdapter : public IAuthProvider{
    XLoginAPI xloginapi;
    public:
        bool login(const string& username, const string& password) override{
            // Normally you'd convert username/password to an secretToken or maybe use an extra API for the same.
    // For demo, we'll just concatenate them as a mock "token."
            string secretToekn = username + "X.com" + password;
            return xloginapi.XSignIn(secretToekn);
        }
    

};

// Client code uses only the expected interface
void authenticateUser(IAuthProvider& provider, const string& username, const string& password) {
    if (provider.login(username, password))
        cout << "User authenticated!\n";
    else
        cout << "Authentication failed!\n";
}

int main() {
    GoogleAdapter googleAuth;
    XAdapter xAuth;
    authenticateUser(googleAuth, "alice@gmail.com", "password123");
    authenticateUser(xAuth, "bob@gmail.com", "abc123");
    return 0;
}

/*
Output:
[GoogleLoginAPI] Signing in with token: alice@gmail.com:password123
User authenticated!

[TwitterLoginAPI] Signing In with secretToken : bob@gmail.comX.comabc123
User authenticated!

*/
// Now, client code works with the Adapter, without caring about the underlying third-party API.
