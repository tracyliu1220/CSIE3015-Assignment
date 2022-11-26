#include "openfhe.h"
#include <bits/stdc++.h>

#include "ciphertext-ser.h"
#include "cryptocontext-ser.h"
#include "key/key-ser.h"
#include "scheme/ckksrns/ckksrns-ser.h"

using namespace lbcrypto;
using namespace std;

// TODO: set SID as last 3 digits of your student id without leading zeros
const double SID = 92;

uint32_t multDepth = 2;
uint32_t scaleModSize = 50;
uint32_t batchSize = 256;

int main() {
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

  // initialize the context
  CCParams<CryptoContextCKKSRNS> parameters;
  parameters.SetMultiplicativeDepth(multDepth);
  parameters.SetScalingModSize(scaleModSize);
  parameters.SetBatchSize(batchSize);
  parameters.SetScalingTechnique(FIXEDMANUAL);
  CryptoContext<DCRTPoly> context = GenCryptoContext(parameters);
  context->Enable(PKE);
  context->Enable(KEYSWITCH);
  context->Enable(LEVELEDSHE);

  // initialize the keys
  KeyPair<DCRTPoly> keyPair;
  keyPair = context->KeyGen();
  context->EvalMultKeyGen(keyPair.secretKey);

  // TODO: pack vectors a and b as plaintexts
  Plaintext ptx_a;
  Plaintext ptx_b;

  // TODO: pack SID as a plaintext
  vector<double> vec_SID(n);
  fill(vec_SID.begin(), vec_SID.end(), SID);
  Plaintext ptx_SID;

  // TODO: encrypt plaintexts as ciphertexts
  Ciphertext<DCRTPoly> ctx_a;
  Ciphertext<DCRTPoly> ctx_b;

  // TODO: calculate ctx_result = (ctx_a + SID) * ctx_b
  Ciphertext<DCRTPoly> ctx_result;

  // serialize
  Serial::SerializeToFile("q1-1_context", context, SerType::BINARY);
  Serial::SerializeToFile("q1-1_ctx_result", ctx_result, SerType::BINARY);
  Serial::SerializeToFile("q1-1_secret_key", keyPair.secretKey,
                          SerType::BINARY);
}
