#include <microhttpd.h>
#include <openssl/ssl.h>  // For OpenSSL initialization
#include <iostream>
#include <string>
#include <fstream>  // For reading key and cert files

// Connection callback function
static MHD_Result answer_to_connection(void *cls, struct MHD_Connection *connection,
                                       const char *url, const char *method,
                                       const char *version, const char *upload_data,
                                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) {
        return MHD_NO;  // Only handle GET requests
    }

    std::string response = "Hello, HTTPS World with OpenSSL!";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
        response.size(), (void*)response.c_str(), MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    
    // Explicitly return MHD_YES or MHD_NO based on the result
    return (ret == MHD_YES) ? MHD_YES : MHD_NO;  // MHD_queue_response returns int, so convert appropriately
}

int main() {
    struct MHD_Daemon *daemon;
    std::string key_content;
    std::string cert_content;

    // Read the key and cert from files
    std::ifstream key_file("server.key");
    if (key_file.is_open()) {
        key_content.assign(std::istreambuf_iterator<char>(key_file), std::istreambuf_iterator<char>());
        key_file.close();
    } else {
        std::cerr << "Error: Could not open server.key" << std::endl;
        return 1;
    }

    std::ifstream cert_file("server.crt");
    if (cert_file.is_open()) {
        cert_content.assign(std::istreambuf_iterator<char>(cert_file), std::istreambuf_iterator<char>());
        cert_file.close();
    } else {
        std::cerr << "Error: Could not open server.crt" << std::endl;
        return 1;
    }

    // Initialize OpenSSL
    OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS | OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);

    // Start the MHD daemon with HTTPS and OpenSSL
    daemon = MHD_start_daemon(
        MHD_USE_SSL | MHD_USE_THREAD_PER_CONNECTION,
        8080,  // Port
        NULL, NULL,  // Accept policy callback
        &answer_to_connection, NULL,  // Connection callback
        MHD_OPTION_HTTPS_MEM_KEY, key_content.c_str(),  // Pass the key content
        MHD_OPTION_HTTPS_MEM_CERT, cert_content.c_str(),  // Pass the cert content
        MHD_OPTION_END
    );

    if (daemon == NULL) {
        std::cerr << "Error starting MHD daemon with OpenSSL." << std::endl;
        return 1;
    }

    std::cout << "HTTPS server running on port 8080 with OpenSSL. Press Enter to stop." << std::endl;
    std::cin.get();  // Wait for user input

    MHD_stop_daemon(daemon);
    return 0;
}
