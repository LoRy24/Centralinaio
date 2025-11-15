//
// Created by loren on 15/11/2025.
//

#include <stdlib.h>

#include "../includes/liste.h"

ListNode* get(int index, ListNode* node) {
    if (node == nullptr || index < 0) {
        return nullptr;
    }

    if (index == 0) {
        return node;
    }

    return get(--index, node->next);
}

void set(ListNode* node, int index, void* value) {
    if (node == nullptr || index < 0) {
        return;
    }

    if (index == 0) {
        node->value = value;
        return;
    }

    set(node->next, --index, value);
}

void insert_top(ListNode** list, ListNode* node) {
    node->next = *list;
    *list = node;
}

void insert_bottom(ListNode* list, ListNode* node) {
    if (list->next == nullptr) {
        list->next = node;
        return;
    }

    insert_bottom(list->next, node);
}

void insert_rec(ListNode* currentNode, ListNode* node, int index) {
    if (currentNode == nullptr) {
        return;
    }

    if (index - 1 == 0) {
        node->next = currentNode->next;
        currentNode->next = node;
        return;
    }

    insert_rec(currentNode->next, node, --index);
}

void insert_to_list(ListNode** list, ListNode* node, const int index) {
    if (index < 0)
        return;

    if (index == 0) {
        insert_top(list, node);
        return;
    }

    insert_rec(*list, node, index);
}

void remove_top(ListNode** list) {
    ListNode* tempNode = *list;
    *list = (*list)->next;
    free(tempNode);
}

void remove_bottom(ListNode* node) {
    if (node->next->next == nullptr) {
        ListNode* tempNode = node->next;
        node->next = nullptr;
        free(tempNode);
        return;
    }

    remove_bottom(node->next);
}

void remove_rec(ListNode* currentNode, int index) {
    if (index - 1 == 0) {
        ListNode* tempNode = currentNode->next;
        currentNode->next = tempNode->next;
        free(tempNode);
        return;
    }

    remove_rec(currentNode->next, --index);
}

void remove_from_list(ListNode** list, const int index) {
    if (index < 0) {
        return;
    }

    if (index == 0) {
        remove_top(list);
        return;
    }

    remove_rec(*list, index);
}

ListNode* create_list(void* value) {
    ListNode* node = malloc(sizeof(ListNode));
    node->value = value;
    node->next = nullptr;
    return node;
}