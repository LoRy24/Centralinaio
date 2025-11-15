//
// Created by loren on 15/11/2025.
//

#ifndef CENTRALINAIO_LISTE_H
#define CENTRALINAIO_LISTE_H

// Nodo lista
typedef struct s_node {
    void* value;
    struct s_node* next;
} ListNode;

// Funzioni per gestire le liste
ListNode* get(int index, ListNode* node);
void set(ListNode* node, int index, void* value);
void insert_top(ListNode** list, ListNode* node);
void insert_bottom(ListNode* list, ListNode* node);
void insert_rec(ListNode* currentNode, ListNode* node, int index);
void insert_to_list(ListNode** list, ListNode* node, int index);
void remove_top(ListNode** list);
void remove_bottom(ListNode* node);
void remove_rec(ListNode* currentNode, int index);
void remove_from_list(ListNode** list, int index);
ListNode* create_list(void* value);

#endif //CENTRALINAIO_LISTE_H