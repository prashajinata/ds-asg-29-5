#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height; // Menyimpan tinggi node dalam AVL tree
};

struct node *newNode(int x)
{
    struct node *currNewNode = (struct node *)malloc(sizeof(struct node));
    currNewNode->key = x;
    currNewNode->left = NULL;
    currNewNode->right = NULL;  
    currNewNode->height = 1; // Inisialisasi tinggi node sebagai 1
    return currNewNode;
}

int max(int a, int b)
{
    return (a > b) ? a : b; // Mengembalikan nilai maksimum antara a dan b
}

int height(struct node *node)
{
    if (node == NULL)
        return 0;        // Jika node kosong, tinggi adalah 0
    return node->height; // Mengembalikan tinggi node
}

int getBalance(struct node *node)
{
    if (node == NULL)
        return 0;                                    // Jika node kosong, balance adalah 0
    return height(node->left) - height(node->right); // Menghitung faktor keseimbangan dari node
}

struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;   // Simpan node x sebagai anak kiri dari y
    struct node *T2 = x->right; // Simpan node T2 sebagai anak kanan dari x
                                // Lakukan rotasi kanan dengan mengubah referensi antara x dan y
    x->right = y;
    y->left = T2;
    // Perbarui tinggi dari node y dan x setelah rotasi
    y->height = max(height(y->left), height(y->right)) + 1; // Mengupdate tinggi node y
    x->height = max(height(x->left), height(x->right)) + 1; // Mengupdate tinggi node x

    return x; // Kembalikan node x yang menjadi root baru setelah rotasi
}

struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1; // Mengupdate tinggi node x
    y->height = max(height(y->left), height(y->right)) + 1; // Mengupdate tinggi node y

    return y; // Mengembalikan root baru setelah rotasi
}

struct node *insert(struct node *root, int x)
{
    if (root == NULL)
        return newNode(x); // Jika root kosong, membuat node baru dengan kunci x

    if (x < root->key)
        root->left = insert(root->left, x); // Jika x lebih kecil dari kunci root, rekursi ke anak kiri
    else if (x > root->key)
        root->right = insert(root->right, x); // Jika x lebih besar dari kunci root, rekursi ke anak kanan
    else
        return root; // Jika x sama dengan kunci root, tidak melakukan apa-apa (tidak ada duplikat)

    root->height = 1 + max(height(root->left), height(root->right)); // Mengupdate tinggi root

    int balance = getBalance(root); // Mendapatkan faktor keseimbangan root

    if (balance > 1 && x < root->left->key)
        return rightRotate(root); // Rotasi kanan tunggal jika x di anak kiri kiri

    if (balance < -1 && x > root->right->key)
        return leftRotate(root); // Rotasi kiri tunggal jika x di anak kanan kanan

    if (balance > 1 && x > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root); // Rotasi kiri kanan jika x di anak kiri kanan
    }

    if (balance < -1 && x < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root); // Rotasi kanan kiri jika x di anak kanan kiri
    }

    return root; // Mengembalikan root setelah operasi penambahan selesai
}

void inorderTraversal(struct node *root)
{
    if (root == NULL)
        return; // Jika root kosong, tidak ada pencetakan yang dilakukan

    inorderTraversal(root->left);  // Rekursi pada anak kiri
    printf(" %d ", root->key);     // Mencetak kunci node saat ini
    inorderTraversal(root->right); // Rekursi pada anak kanan
}

struct node *freeAll(struct node *root)
{
    if (root == NULL)
        return NULL; // Jika root kosong, tidak ada pembebasan memori yang dilakukan

    root->left = freeAll(root->left);   // Rekursi pada anak kiri
    root->right = freeAll(root->right); // Rekursi pada anak kanan

    free(root); // Membebaskan memori dari root saat ini
    return NULL;
}

struct node *predecessor(struct node *root)
{
    struct node *curr = root->left;
    while (curr->right != NULL)
    {
        curr = curr->right;
    }
    return curr; // Mengembalikan predecessor dari root
}

struct node *deleteValue(struct node *root, int x)
{
    if (root == NULL)
        return NULL; // Jika root kosong, tidak ada yang dihapus

    if (x < root->key)
        root->left = deleteValue(root->left, x); // Jika x lebih kecil dari kunci root, rekursi ke anak kiri
    else if (x > root->key)
        root->right = deleteValue(root->right, x); // Jika x lebih besar dari kunci root, rekursi ke anak kanan
    else
    {
        // Data ditemukan. Proses penghapusan dapat dilakukan
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct node *temp = NULL;
            if (root->left != NULL)
                temp = root->left; // Jika hanya memiliki anak kiri, root diganti dengan anak kiri
            else
                temp = root->right; // Jika hanya memiliki anak kanan, root diganti dengan anak kanan

            if (temp == NULL)
            {
                temp = root;
                root = NULL; // Jika root tidak memiliki anak, root dihapus
            }
            else
            {
                *root = *temp; // Jika root memiliki satu anak, root diganti dengan anak tersebut
            }
            free(temp); // Membebaskan memori dari temp
        }
        else
        {
            // Menggunakan predecessor: node terbesar dari subtree kiri
            struct node *temp = predecessor(root);
            root->key = temp->key; // Mengganti kunci root dengan kunci predecessor

            root->left = deleteValue(root->left, temp->key); // Rekursi untuk menghapus predecessor dari anak kiri
        }
    }

    if (root == NULL)
        return root; // Jika root kosong setelah penghapusan, mengembalikan NULL

    root->height = 1 + max(height(root->left), height(root->right)); // Mengupdate tinggi root

    int balance = getBalance(root); // Mendapatkan faktor keseimbangan root

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root); // Rotasi kanan tunggal jika faktor keseimbangan tidak merusak setelah penghapusan

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root); // Rotasi kiri kanan jika faktor keseimbangan merusak setelah penghapusan
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root); // Rotasi kiri tunggal jika faktor keseimbangan tidak merusak setelah penghapusan

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root); // Rotasi kanan kiri jika faktor keseimbangan merusak setelah penghapusan
    }

    return root; // Mengembalikan root setelah operasi penghapusan selesai
}