#include "openfhe.h"
#include <bits/stdc++.h>

#include "ciphertext-ser.h"
#include "cryptocontext-ser.h"
#include "key/key-ser.h"
#include "scheme/ckksrns/ckksrns-ser.h"

using namespace lbcrypto;
using namespace std;

uint32_t multDepth = 1;
uint32_t scaleModSize = 50;
uint32_t batchSize = 256;

int main(int argc, char *argv[]) {
  // input
  int n;
  cin >> n;
  vector<double> p(n), q(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> q[i];
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

  // pack vectors a and b as plaintexts
  Plaintext ptx_p = context->MakeCKKSPackedPlaintext(p);
  Plaintext ptx_q = context->MakeCKKSPackedPlaintext(q);

  // encrypt plaintexts as ciphertexts
  Ciphertext<DCRTPoly> ctx_p = context->Encrypt(keyPair.publicKey, ptx_p);
  Ciphertext<DCRTPoly> ctx_q = context->Encrypt(keyPair.publicKey, ptx_q);

  // serialize
  Serial::SerializeToFile("q1-2_context", context, SerType::BINARY);
  Serial::SerializeToFile("q1-2_ctx_p", ctx_p, SerType::BINARY);
  Serial::SerializeToFile("q1-2_ctx_q", ctx_q, SerType::BINARY);

  std::ofstream multKeyFile("q1-2_mult_key", std::ios::out | std::ios::binary);
  context->SerializeEvalMultKey(multKeyFile, SerType::BINARY);
  multKeyFile.close();

  // serialize secret key for judge
  Serial::SerializeToFile("q1-2_secret_key", keyPair.secretKey,
                          SerType::BINARY);
}
