#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    int contact_id;
    char name[50];
    char phone[20];
    char email[50];
    struct Contact *next;
};

struct Contact *head = NULL;

// Add contact at end
void addContact() {
    struct Contact *new_contact = (struct Contact *)malloc(sizeof(struct Contact));
    if (!new_contact) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Contact ID (int): ");
    scanf("%d", &new_contact->contact_id);
    getchar(); // clear newline

    printf("Enter Name: ");
    scanf(" %[^\n]", new_contact->name);

    printf("Enter Phone: ");
    scanf(" %[^\n]", new_contact->phone);

    printf("Enter Email: ");
    scanf(" %[^\n]", new_contact->email);

    new_contact->next = NULL;

    // Check for duplicate ID
    struct Contact *temp = head;
    while (temp) {
        if (temp->contact_id == new_contact->contact_id) {
            printf("Contact ID already exists!\n");
            free(new_contact);
            return;
        }
        temp = temp->next;
    }

    // Insert at end
    if (!head) {
        head = new_contact;
    } else {
        temp = head;
        while (temp->next) temp = temp->next;
        temp->next = new_contact;
    }

    printf("Contact added successfully!\n");
}

// Display all contacts
void displayContacts() {
    if (!head) {
        printf("No contacts found.\n");
        return;
    }
    struct Contact *temp = head;
    while (temp) {
        printf("ID: %d | Name: %s | Phone: %s | Email: %s\n",
               temp->contact_id, temp->name, temp->phone, temp->email);
        temp = temp->next;
    }
}

// Search contact (exact match)
void searchContact() {
    if (!head) {
        printf("No contacts found.\n");
        return;
    }

    int choice;
    printf("Search by: 1. Name  2. Contact ID\nEnter choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        char search_name[50];
        printf("Enter Name to search: ");
        scanf(" %[^\n]", search_name);

        struct Contact *temp = head;
        int found = 0;
        while (temp) {
            if (strcmp(temp->name, search_name) == 0) {
                printf("Found: ID: %d | Name: %s | Phone: %s | Email: %s\n",
                       temp->contact_id, temp->name, temp->phone, temp->email);
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found) printf("Contact not found.\n");
    } else if (choice == 2) {
        int search_id;
        printf("Enter Contact ID: ");
        scanf("%d", &search_id);

        struct Contact *temp = head;
        int found = 0;
        while (temp) {
            if (temp->contact_id == search_id) {
                printf("Found: ID: %d | Name: %s | Phone: %s | Email: %s\n",
                       temp->contact_id, temp->name, temp->phone, temp->email);
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found) printf("Contact not found.\n");
    } else {
        printf("Invalid choice!\n");
    }
}

// Update contact by ID
void updateContact() {
    if (!head) {
        printf("No contacts found.\n");
        return;
    }
    int id, found = 0;
    printf("Enter Contact ID to update: ");
    scanf("%d", &id);
    getchar();

    struct Contact *temp = head;
    while (temp) {
        if (temp->contact_id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", temp->name);
            printf("Enter New Phone: ");
            scanf(" %[^\n]", temp->phone);
            printf("Enter New Email: ");
            scanf(" %[^\n]", temp->email);
            printf("Contact updated!\n");
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (!found) printf("Contact ID not found.\n");
}

// Delete contact by ID
void deleteContact() {
    if (!head) {
        printf("No contacts found.\n");
        return;
    }
    int id;
    printf("Enter Contact ID to delete: ");
    scanf("%d", &id);

    struct Contact *temp = head, *prev = NULL;
    while (temp) {
        if (temp->contact_id == id) {
            if (!prev) {
                head = temp->next; // delete first node
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Contact deleted!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Contact ID not found.\n");
}

// Bubble Sort by Name (Fixed)
// Bubble Sort by Name (swap data only — do NOT change next pointers)
void sortContacts() {
    if (!head || !head->next) {
        printf("Not enough contacts to sort.\n");
        return;
    }

    int swapped;
    struct Contact *ptr1;
    struct Contact *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                // swap contact_id
                int tmp_id = ptr1->contact_id;
                ptr1->contact_id = ptr1->next->contact_id;
                ptr1->next->contact_id = tmp_id;

                // swap name
                char tmp_name[50];
                strcpy(tmp_name, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tmp_name);

                // swap phone
                char tmp_phone[20];
                strcpy(tmp_phone, ptr1->phone);
                strcpy(ptr1->phone, ptr1->next->phone);
                strcpy(ptr1->next->phone, tmp_phone);

                // swap email
                char tmp_email[50];
                strcpy(tmp_email, ptr1->email);
                strcpy(ptr1->email, ptr1->next->email);
                strcpy(ptr1->next->email, tmp_email);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Contacts sorted alphabetically!\n");
}



// Main Menu
int main() {
    int choice;
    do {
        printf("\n--- Contact Management System ---\n");
        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Sort Contacts Alphabetically\n");
        printf("5. Update Contact\n");
        printf("6. Delete Contact\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: sortContacts(); break;
            case 5: updateContact(); break;
            case 6: deleteContact(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 7);

    // Free all nodes before exiting
    struct Contact *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
