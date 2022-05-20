// header for gpgme
#include <gpgme.h>
#include <iostream>


int main() {
  gpgme_ctx_t ctx;
  gpgme_error_t err;
  gpgme_data_t sig, text;
  gpgme_verify_result_t result;


  // initialize the library
  gpgme_check_version(NULL);

  err = gpgme_new(&ctx);
  if (err != GPG_ERR_NO_ERROR)
    std::cerr << "gpgme_new failed: " << gpgme_strerror(err) << std::endl;
  
  err = gpgme_data_new_from_file(&sig, "test.so.sig", 1);
  if (err != GPG_ERR_NO_ERROR)
    std::cerr << "gpgme_data_new_from_file failed: " << gpgme_strerror(err) << std::endl;

  err = gpgme_data_new_from_file(&text, "test.so", 1);
  if (err != GPG_ERR_NO_ERROR)
    std::cerr << "gpgme_data_new_from_file failed: " << gpgme_strerror(err) << std::endl;

  err = gpgme_op_verify(ctx, sig, text, NULL);
  if (err != GPG_ERR_NO_ERROR)
    std::cerr << "gpgme_op_verify failed: " << gpgme_strerror(err) << std::endl;

  result = gpgme_op_verify_result(ctx);
  if (!result->signatures || result->signatures->next) {
    std::cerr << "verification failed" << std::endl;
    return 1;
  }
  std::cout << "No Error " << GPG_ERR_NO_ERROR << std::endl;
  if (result->signatures) {
    gpgme_signature_t sig1 = result->signatures;
    std::cout << "Signature status: " << sig1->status << std::endl;
    std::cout << "Signature fingerprint: " << sig1->fpr << std::endl;
    std::cout << "Signature summary: " << sig1->summary << std::endl;
  }
  else
    std::cout << "No signatures found." << std::endl;
}