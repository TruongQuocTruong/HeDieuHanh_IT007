#include <stdlib.h>
#include <stdio.h>
#define MAX_SEQ 100


int frame = 3;
int length = 11;
int DefaultSeq[11] = {1, 9, 5, 2, 2, 4, 4, 6, 0, 0, 7};
int choice;
int seq[MAX_SEQ];
char Ans[MAX_SEQ];
int Page[MAX_SEQ][MAX_SEQ];

void Create() {
	for (int i = 0; i < frame; i++) {
		Ans[i] = '*';
		for (int j = 0; j < i; j++) {
			Page[i][j] =  -1;
		}
		for (int j = i; j < frame; j++) {

			Page[i][j] = seq[i];
		}
	}
}

void FIFO() {
	Create();
	int curr = 0;
	int Found = 0;
	
	for (int j = frame; j < length; j++) {
		for (int i = 0; i < frame; i++) {
				Page[i][j] = Page[i][j-1];
				if (Page[i][j] == seq[j]) {
					Found = 1;
				}
		}
		
		if (Found == 1) {
			Ans[j] = ' ';
			Found = 0;
		} 
		else {
			Ans[j] = '*';
			Page[curr][j] = seq[j];
			curr = (curr + 1) % frame;
		}
	}
}

void OPT() {
	Create();
	int next[MAX_SEQ];
	int curr[MAX_SEQ];
	int Found = 0;
	
	for (int i = 0; i < frame; i++) {
		curr[i] = i;
	}
	
	for (int i = 0; i < length; i++) {
		next[i] = MAX_SEQ;
		for (int j = i + 1; j < length; j++) {
			if (seq[i] == seq[j]) {
				next[i] = j;
				break;
			}
		}
	}
	
	for (int j = frame; j < length; j++) {
		for (int i = 0; i < frame; i++) {
				Page[i][j] = Page[i][j-1];
				if (Page[i][j] == seq[j]) {
					Found = 1;
					curr[i] = j;
				}
		}
		
		if (Found == 1) {
			Ans[j] = ' ';
			Found = 0;
		} 
		else {
			int pos = 0;
			Ans[j] = '*';
			for (int i = 1; i < frame; i++) {
				if (next[curr[pos]] < next[curr[i]]) {
					pos = i;
				}
			}
			

			Page[pos][j] = seq[j];
			curr[pos] =j;
		}
	}
}

void LRU() {
	Create();
	int curr[MAX_SEQ];
	int Found = 0;
	
	for (int i = 0; i < frame; i++) {
		curr[i] = i;
	}
	
	for (int j = frame; j < length; j++) {
		for (int i = 0; i < frame; i++) {
				Page[i][j] = Page[i][j-1];
				if (Page[i][j] == seq[j]) {
					Found = 1;
					curr[i] = j;
				}
		}
		
		if (Found == 1) {
			Ans[j] = ' ';
			Found = 0;
		} 
		else {
			int pos = 0;
			Ans[j] = '*';
			for (int i = 1; i < frame; i++) {
				if (curr[pos] < curr[i]) {
					pos = i;
				}
			}
			
			Page[pos][j] = seq[j];
			curr[pos] =j;
		}
	}
}

void InputSeq() {
	if (choice == 1) {
		for (int i = 0; i < length; i++) {
			seq[i] = DefaultSeq[i];
		}
		printf("\n");
		printf("--- Page Replacement Algorithm ---\n");
		printf("Input page frames: ");
		scanf("%d", &frame);
	}
	else if (choice == 2) {
		printf("Input seq's length: ");
		scanf("%d", &length);
		printf("Input your seq: ");
		for (int i = 0; i < length; i++) {
			scanf("%d", &seq[i]);
		}
		printf("\n");
		printf("--- Page Replacement Algorithm ---\n");
		printf("Input page frames: ");
		scanf("%d", &frame);
	}
}

void Output() {
	for (int i = 0; i < length; i++) 
		printf("%d ", seq[i]);
	printf("\n");
	for (int i = 0; i < frame; i++) {
		for (int j = 0; j < length; j++) {
			if (Page[i][j] == -1) {
				printf("  ");
			}
			else {
				printf("%d ", Page[i][j]);
			}
		}
		printf("\n");
	}
	int cnt = 0;
	for (int i = 0; i < length; i++) {
		if (Ans[i] == '*')
			cnt++;
		printf("%c ", Ans[i]);
	}
	printf("\n");
	printf("Number of Page Fault: %d\n", cnt);
}
void MENU() {
	printf("--- Page Replacement Algorithm ---\n");
	printf("1. Default referenced sequence\n");
	printf("2. Manual input sequence\n");
}

void Solve() {
	printf("\n");
	printf("--- Page Replacement Algorithm ---\n");
	printf("1. FIFO algorithm\n");
	printf("2. OPT algorithm\n");
	printf("3. LRU algorithm\n");
	printf("4. All algorithm\n");
	
	printf("\n");
	printf("Input your choice: ");
	scanf("%d", &choice);
	
	if (choice == 1) {
		FIFO();
		Output();
	}
	else if (choice == 2) {
		OPT();
		Output();
	}
	else if (choice == 3) {
		LRU();
		Output();
	}
	else if (choice == 4) {
		printf("FIFO\n");
		FIFO();
		Output();
		printf("\n");
		printf("OPT\n");
		OPT();
		Output();
		printf("\n");
		printf("LRU\n");
		LRU();
		Output();
		printf("\n");
		
	}
	else return;
	
}

void Input() {
	printf("\n");
	printf("Input your choice: ");
	scanf("%d", &choice);
	InputSeq();
}

int main() {
	MENU();
	Input();
	Solve();
}


