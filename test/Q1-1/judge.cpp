#include "openfhe.h"
#include <bits/stdc++.h>

#include "ciphertext-ser.h"
#include "cryptocontext-ser.h"
#include "key/key-ser.h"
#include "scheme/ckksrns/ckksrns-ser.h"

using namespace lbcrypto;
using namespace std;

int main(int argc, char *argv[]) {
  string str_SID(argv[1]);
  str_SID = str_SID.substr(1, str_SID.size());

  int SID;
  stringstream ss;
  ss << str_SID;
  ss >> SID;

  SID = SID % 1000;

  // input
  int n;
  cin >> n;
  vector<double> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  // deserialize context
  CryptoContext<DCRTPoly> context;
  Serial::DeserializeFromFile("q1-1_context", context, SerType::BINARY);

  // deserialize secret key
  PrivateKey<DCRTPoly> secret_key;
  Serial::DeserializeFromFile("q1-1_secret_key", secret_key, SerType::BINARY);

  // deserialize ctx_result
  Ciphertext<DCRTPoly> ctx_result;
  Serial::DeserializeFromFile("q1-1_ctx_result", ctx_result, SerType::BINARY);

  if (ctx_result->GetLevel() < 1) {
    cout << "\033[38;5;009mFAILED\033[0m (the level of ctx_result is incorrect)"
         << endl;
    exit(0);
  }

  // decrypt the result
  Plaintext ptx_result;
  context->Decrypt(secret_key, ctx_result, &ptx_result);
  ptx_result->SetLength(n);
  vector<double> result = ptx_result->GetRealPackedValue();

  // check
  bool correct = true;
  for (int i = 0; i < n; i++) {
    // cout << (a[i] + SID) * b[i] << ' ' << result[i] << endl;
    if (abs((a[i] + SID) * b[i] - result[i]) > 0.001) {
      correct = false;
      break;
    }
  }

  cout << ((correct == true) ? "\033[38;5;120mPASSED" : "\033[38;5;009mFAILED")
       << "\033[0m" << endl;
}
