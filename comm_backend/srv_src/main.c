#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024
#define BEGIN_SPECIFIER "<BEGIN>"
#define END_SPECIFIER "<END>"
#define MAX_COMMAND_DATA_LENGTH 128

typedef struct {
    uint32_t session_token;
    uint8_t command;
    uint16_t command_data_length;
    uint8_t command_data[MAX_COMMAND_DATA_LENGTH];
    uint8_t padding_length;
    uint8_t padding[3];
    uint32_t checksum;
    uint32_t sequence_number;
} data_pkt_t;

typedef struct {
    uint32_t session_token;
    uint8_t acknowledgement_command;
    uint32_t sequence_number;
} ack_pkt_t;

void INTERNET_TRANSMITE_PREPARE_DATAPKT(data_pkt_t *pkt) {
    pkt->session_token = htonl(pkt->session_token);
    pkt->command_data_length = htons(pkt->command_data_length);
    pkt->checksum = htonl(pkt->checksum);
    pkt->sequence_number = htonl(pkt->sequence_number);
}

void INTERNET_TRANSLATE_PREPARE_ACK_PKT(ack_pkt_t *pkt) {
    pkt->session_token = htonl(pkt->session_token);
    pkt->sequence_number = htonl(pkt->sequence_number);
}

void INTERNET_TRANSMITE_PREPARE_DATAPKT(data_pkt_t *pkt) {
    pkt->session_token = htonl(pkt->session_token);
    pkt->command_data_length = htons(pkt->command_data_length);
    pkt->checksum = htonl(pkt->checksum);
    pkt->sequence_number = htonl(pkt->sequence_number);
}

void INTERNET_TRANSLATE_PREPARE_ACK_PKT(ack_pkt_t *pkt) {
    pkt->session_token = htonl(pkt->session_token);
    pkt->sequence_number = htonl(pkt->sequence_number);
}

void parse_data_pkt(data_pkt_t *pkt, uint8_t *buffer) {
    memcpy(&pkt->session_token, buffer, sizeof(pkt->session_token));
    buffer += sizeof(pkt->session_token);
    memcpy(&pkt->command, buffer, sizeof(pkt->command));
    buffer += sizeof(pkt->command);
    memcpy(&pkt->command_data_length, buffer, sizeof(pkt->command_data_length));
    buffer += sizeof(pkt->command_data_length);
    memcpy(pkt->command_data, buffer, pkt->command_data_length);
    buffer += pkt->command_data_length;
    memcpy(&pkt->padding_length, buffer, sizeof(pkt->padding_length));
    buffer += sizeof(pkt->padding_length);
    memcpy(pkt->padding, buffer, pkt->padding_length);
    buffer += pkt->padding_length;
    memcpy(&pkt->checksum, buffer, sizeof(pkt->checksum));
    buffer += sizeof(pkt->checksum);
    memcpy(&pkt->sequence_number, buffer, sizeof(pkt->sequence_number));
}

void parse_ack_pkt(ack_pkt_t *pkt, uint8_t *buffer) {
    memcpy(&pkt->session_token, buffer, sizeof(pkt->session_token));
    buffer += sizeof(pkt->session_token);
    memcpy(&pkt->acknowledgement_command, buffer, sizeof(pkt->acknowledgement_command));
    buffer += sizeof(pkt->acknowledgement_command);
    memcpy(&pkt->sequence_number, buffer, sizeof(pkt->sequence_number));
}

data_pkt_t build_data_pkt(uint32_t session_token, uint8_t command, uint8_t *command_data, uint16_t command_data_length, uint32_t sequence_number) {
    data_pkt_t pkt;
    pkt.session_token = session_token;
    pkt.command = command;
    pkt.command_data_length = command_data_length;
    memcpy(pkt.command_data, command_data, command_data_length);
    pkt.padding_length = (4 - command_data_length % 4) % 4;
    memset(pkt.padding, 0, pkt.padding_length);
    pkt.checksum = 0; // TODO: Calculate checksum
    pkt.sequence_number = sequence_number;
    return pkt;
}

ack_pkt_t build_ack_pkt(uint32_t session_token, uint32_t sequence_number) {
    ack_pkt_t pkt;
    pkt.session_token = session_token;
    pkt.acknowledgement_command = 0; // TODO: Define acknowledgement command
    pkt.sequence_number = sequence_number;
    return pkt;
}

typedef struct {
    int socket;
    struct sockaddr_in address;
    int addr_len;
} client_t;

client_t *clients[MAX_CLIENTS] = {NULL};
static ssize_t clients_len = 0;

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// TODO: Implement the add_client function
void add_client(client_t *client) {
    pthread_mutex_lock(&clients_mutex);
    // Add the client to the first available slot in the clients array
    clients= realloc(clients, (clients_len+1)*sizeof(client_t *));
    clients[clients_len] = client;
    clients_len++;
    pthread_mutex_unlock(&clients_mutex);
}

// TODO: Implement the remove_client function
void remove_client(int socket) {
    pthread_mutex_lock(&clients_mutex);
    // Remove the client with the given socket from the clients array
    pthread_mutex_unlock(&clients_mutex);
}

// TODO: Implement the find_client function
client_t *find_client(int socket) {
    pthread_mutex_lock(&clients_mutex);
    // Find the client with the given socket in the clients array
    pthread_mutex_unlock(&clients_mutex);
    return NULL; // Replace with the found client or NULL if not found
}

void *handle_client(void *arg) {
    char buffer[BUFFER_SIZE];
    client_t *cli = (client_t *)arg;

    // TODO: Add your protocol handling code here

    remove_client(cli->socket);
    close(cli->socket);
    free(cli);
    pthread_detach(pthread_self());

    return NULL;
}

int main() {
    int server_sock, client_sock, addr_len;
    struct sockaddr_in server_addr, client_addr;
    pthread_t tid;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5000);
    addr_len = sizeof(struct sockaddr_in);

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);

    printf("Server is listening on port 5000...\n");

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);

        // Check if max clients is reached
        if ((cli_count + 1) == MAX_CLIENTS) {
            printf("Max clients reached. Rejected: ");
            print_client_addr(&client_addr);
            printf("\n");
            close(client_sock);
            continue;
        }

        // Client settings
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->address = client_addr;
        cli->addr_len = addr_len;
        cli->socket = client_sock;

        add_client(cli);

        // Add client to the queue and fork thread
        pthread_create(&tid, NULL, &handle_client, (void *)cli);

        // Reduce CPU usage
        sleep(1);
    }

    return EXIT_SUCCESS;
}

