#include <iostream>

using namespace std;

struct Branche  {
    int status;
    //bool is_trunk;
    Branche * prev;
    Branche * left;
    Branche * right;
};

/*
typedef struct tree_s   
{
    Branche * root;
} Tree;

Tree * create (void)    
{
    Tree * tree;

    tree = calloc (1, sizeof *tree);
    if (NULL == tree)   cout << "ERROR: Cannot allocate memory!";

    return tree;
}   //*/

/*  This function creates the trunk of the tree, which differs from the other branches
in that, that its 'previous'-pointer is NULL and status always '0'                  */
Branche * create_trunk (void)
{
    Branche * branche;
    // allocate memory and check
    branche = (Branche*) malloc (sizeof *branche);
    if (NULL == branche)    {
        cout << "ERROR: Cannot allocate memory!";
        return NULL;
    }    

    branche->status = 0;
    //branche->is_trunk = true;
    branche->left = NULL;
    branche->right = NULL;
    branche->prev = NULL;

    return branche;
}

/*  This function adds a branche to the tree. It takes arguments for weither the branch is
appended to the left or right and if it can be used for laundry drying (status = 1). If an
invalid argument is passed for the position, the function prints a notification, the parent 
is returned and a new "append" with valid arguments can be tried.                         */
Branche * append (Branche * parent, int status, char side)
{
    Branche * branche;
    // allocate memory and check
    branche = (Branche*) malloc (sizeof *branche);
    if (NULL == branche)    {
        cout << "ERROR: Cannot allocate memory!";
        return NULL;
    }    

    branche->status = status;
    //branche->is_trunk = false;
    branche->left = NULL;
    branche->right = NULL;
    branche->prev = parent;

    if (side == 'l' ) {
        parent->left = branche; 
    }   else if (side == 'r')   {
        parent->right = branche;
    }   else    {   
        cout << "Can´t append - only 'l' or 'r' as argument accepted!\n";
        free (branche);
        return parent; 
    }    

    return branche;
}

/*  This function enables to move in the tree, primarily for the tree creation/growing process.
Possible movements are up ('u'), down left ('l') and down right ('r'). If an invalid direction 
argument is passed, the initial branche is returned and moving can be tried again.          */
Branche* move_in_tree(Branche * current, char direc)
{
    if (direc == 'u')   {
        return current->prev;
    }   else if (direc == 'l')  {
        return current->left;
    }   else if (direc == 'r')  {
        return current->right;
    }   else    {
        cout << "Invalid choice, choices are: 'u' (up) / 'l' (left) / 'r' (right)\n";
        return current;
    }
}

/*  This function prints the status values of the branches in a recursive manner, if it gets called  
by the main function once with a pointer to the trunk. It starts with the trunk value and continues
with the most left "branch-of-branches", progressing right-wards and ends at the right-most branche. */
void print_tree (Branche * current)
{
    /*
    Branche * branche;
    branche = tree->root;
    while ( branche->used != true ) {
        cout << branche->status << " ";
        branche->used = true;
        if ()
    }   //*/

    // check if pointer is valid 
    if (current == NULL)   {
        cout << "Empty tree\n";
    }
    
    cout << " " << current->status;     // print current branche

    // recursive function: navigate through the tree in left-right order
    if (current->left != NULL)  print_tree(current->left);   
    if (current->right != NULL) print_tree(current->right);   
}

/*  This function prunes the tree by moving to the edges and removing every edge with status '0'.
The function also realizes if a branche in the tree becomes an edge during the pruning process,
removing it too, if it has status '0'. The memory of all removed (pruned) branches is set free. */
Branche * prune(Branche * current)
{
    if (current == NULL)    return NULL;    // branche is NULL pointer
    // recursive function: navigate through the tree in left-right order
    if (prune(current->left) == NULL)   current->left = NULL;   // edge was removed, reset pointer
    if (prune(current->right) == NULL)  current->right = NULL;  // edge was removed, reset pointer
    
    // check: keep branche, if it has status '1' or is no edge after pruning of children
    if ((current->status == 1) || current->left != NULL || current->right != NULL)  return current;
    
    // branche is edge and has status '0' -> free memory and return NULL pointer
    free (current);
    return NULL;
}

int main()
{
    Branche * trunk = create_trunk();
    Branche * current = trunk;

    // create left side of example tree
    current = append(current, 0, 'l');
    current = append(current, 1, 'l');
    current = move_in_tree(current, 'u');
    current = append(current, 0, 'r');
    
    // check tree by printing
    cout << "\n" << "Print left tree: ";
    print_tree(trunk);

    // reset current to trunk and create right side of example tree
    current = trunk;      
    current = append(current, 1, 'r');
    current = append(current, 1, 'l');
    current = move_in_tree(current, 'u');
    current = append(current, 0, 'r');
    current = append(current, 0, 'l');
    current = move_in_tree(current, 'u');
    current = append(current, 0, 'r');  
    // print full example tree
    cout << "\n" << "Print full tree: ";
    print_tree(trunk);          

    // execute and check pruning
    cout << "\n" << "Start pruning now..";
    current = prune(trunk);
    cout << "\n" << "Pruning finished, pruned tree: ";
    print_tree(trunk);

    return 0;
}