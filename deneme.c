#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Komut düğümü için yapı tanımı
typedef struct CommandNode {
	char *command;
	struct CommandNode *next;
} CommandNode;

// Yeni bir komut düğümü oluştur
CommandNode *createCommandNode(const char *command) {
	CommandNode *node = (CommandNode *)malloc(sizeof(CommandNode));
	node->command = strdup(command);
	node->next = NULL;
	return node;
}

// Komut listesine yeni bir komut ekle
void addCommand(CommandNode **head, const char *command) {
	CommandNode *newNode = createCommandNode(command);
	if (*head == NULL) {
		*head = newNode;
	} else {
		CommandNode *temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

// Verilen komutları zincirleme şeklinde çalıştır
void executeCommands(CommandNode *head) {
	int pipefd[2];
	int input_fd = STDIN_FILENO;
	while (head != NULL) {
		pipe(pipefd); // Yeni bir pipe oluştur
		pid_t pid = fork(); // Yeni bir süreç oluştur
		if (pid == 0) { // Alt süreç
			dup2(input_fd, STDIN_FILENO); // Girdiyi ayarla
			if (head->next != NULL) { // Son komut değilse, çıktıyı pipe'a yönlendir
				dup2(pipefd[1], STDOUT_FILENO);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			execlp(head->command, head->command, NULL); // Komutu çalıştır
			perror("execlp failed");
			exit(EXIT_FAILURE);
		} else { // Ana süreç
			wait(NULL); // Alt sürecin bitmesini bekle
			close(pipefd[1]); // Pipe'ın yazma uçlarını kapat
			input_fd = pipefd[0]; // Bir sonraki komut için girdi olarak kullan
			head = head->next; // Bir sonraki komuta geç
		}
	}
}

// Komut listesini serbest bırak
void freeCommandList(CommandNode *head) {
	while (head != NULL) {
		CommandNode *temp = head;
		head = head->next;
		free(temp->command);
		free(temp);
	}
}

int main() {
	CommandNode *head = NULL;
	char commandBuffer[100]; // Max komut uzunluğu

	printf("Enter commands (type 'done' to finish):\n");

	// Kullanıcıdan komutları al
	while (1) {
		printf("> ");
		fgets(commandBuffer, sizeof(commandBuffer), stdin);
		commandBuffer[strcspn(commandBuffer, "\n")] = 0; // Satır sonu karakterini kaldır

		if (strcmp(commandBuffer, "done") == 0) {
			break; // Kullanıcı 'done' yazarsa döngüden çık
		}

		addCommand(&head, commandBuffer); // Komutu listeye ekle
	}

	// Komutları çalıştır
	executeCommands(head);

	// Komut listesini serbest bırak
	freeCommandList(head);

	return 0;
}
