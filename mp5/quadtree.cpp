/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

#include "quadtree.h"

using namespace std;

/**
 * Quadtree constructor: creates an empty quadtree
 */
Quadtree::Quadtree()
{
    root = NULL;
}

/**
 * Quadtree constructor: creates a quadtree with the buildTree function
 */
Quadtree::Quadtree(PNG const & source, int resolution)
{
    buildTree(source, resolution);
}

/**
 * Quadtree Copy constructor: copies one quadtree to this quadtree
 */
Quadtree::Quadtree(Quadtree const & other)
{
    root = copy(other.root);
}

/**
 * Quadtree Copy helper function
 * @params: Quadtree*
 * @return: Quadtree*
 * Description:
 * Recursive function, checks if node is NULL
 * if Node not NULL, create a new node, create new nodes for nwChild, neChild, swChild, and seChild recursively
 * return the node
 */
Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* node)
{
    if(node != NULL) {
        QuadtreeNode* newNode = new QuadtreeNode(node);
        newNode->nwChild = copy(node->nwChild);
        newNode->neChild = copy(node->neChild);
        newNode->swChild = copy(node->swChild);
        newNode->seChild = copy(node->seChild);
        return newNode;
    }
    return node;
}

/**
 * Quadtree Destructor
 * @params: 
 * @return: 
 * Description:
 * Destructor that deletes this quadtree
 */
Quadtree::~Quadtree()
{
    clear(root);
}

/**
 * Clear function
 * @params: QuadtreeNode*
 * @return: void
 * Description:
 * clear function deletes the quadtree starting that the provided node
 * checks if the node is NULL
 * if not, recursively clear the quadtreenode children nwChild, neChild, swChild, seChild
 * delete the current node
 * set node to null
 */
void Quadtree::clear(QuadtreeNode* &node)
{
    if(node != NULL) {
        clear(node->nwChild);
        clear(node->neChild);
        clear(node->swChild);
        clear(node->seChild);
        delete node;
        node = NULL;
    }
    return;
}

/**
 * =operater
 * @params: other Quadtree
 * @return: Quadtree
 * Description:
 * assigns values from other quadtree to this quadtree
 */
Quadtree const & Quadtree::operator=(Quadtree const & other)
{
    if(root != other.root) {
        clear(root);
        root = copy(other.root);
    }
    return *this;
}

/**
 * buildTree function
 * @params: PNG, int
 * @return: void
 * Description:
 * builds a new tree from the provided PNG and resolution parameter
 */
void Quadtree::buildTree(PNG const & source, int resolution)
{
    root = new QuadtreeNode(0, 0, resolution);
    buildTree(source, resolution, root);
}

/**
 * buildTree helper function
 * @params: PNG, int, QuadtreeNode*
 * @return: void
 * Description:
 * Function that actually builds the tree recursively
 * Base Case - if the resolution is 1, node is a 1x1 pixel, assign PNG pixel at x,y to that node
 * Create new quadtree nodes for node's children with the corret x,y coordinates and resolution sizes(/2)
 * Assign the values of the RGBAPixel to the average of the RGBAPixel values of its children
 */
void Quadtree::buildTree(PNG const & source, int resolution, QuadtreeNode* node)
{
    if(resolution == 1) {
        node->element = *source(node->x, node->y);
        return;
    }

    node->nwChild = new QuadtreeNode(node->x, node->y, resolution/2);
    node->neChild = new QuadtreeNode(node->x + resolution/2, node->y, resolution/2);
    node->swChild = new QuadtreeNode(node->x, node->y + resolution/2, resolution/2);
    node->seChild = new QuadtreeNode(node->x + resolution/2, node->y + resolution/2, resolution/2);

    buildTree(source, resolution/2, node->nwChild);
    buildTree(source, resolution/2, node->neChild);
    buildTree(source, resolution/2, node->swChild);
    buildTree(source, resolution/2, node->seChild);

    node->element.red = (node->nwChild->element.red + node->neChild->element.red
			+ node->swChild->element.red + node->seChild->element.red)/4;
    node->element.green = (node->nwChild->element.green + node->neChild->element.green
			+ node->swChild->element.green + node->seChild->element.green)/4;
    node->element.blue = (node->nwChild->element.blue + node->neChild->element.blue
			+ node->swChild->element.blue + node->seChild->element.blue)/4;
}

/**
 * getPixel function
 * @params: int x and y
 * @return: RGBAPixel
 * Description:
 * return the pixel at the x,y coordinate
 */
RGBAPixel Quadtree::getPixel(int x, int y) const
{
    return getPixel(x,y,root);
}

/**
 * getPixel helper function
 * @params: int x and y, QuadtreeNode*
 * @return: RGBAPixel
 * Description:
 * getPixel helper function that actually performs the getting of the pixel, recursive function
 * Base Case: if reached the x,y coordinate and its resolution is 1, or no more children, return node's RGBApixel
 * Traverse the quadtree until you reach the correct x,y coordinate with the isInPixel helper function
 */
RGBAPixel Quadtree::getPixel(int x, int y, QuadtreeNode* node) const
{
    if( (node->x == x && node->y == y && node->r == 1)  ||
        (node->nwChild == NULL && node->neChild == NULL && node->swChild == NULL && node->seChild == NULL)  ) {
        return node->element;
    } else if(isInPixel(x,y,node->nwChild)) {
        return getPixel(x,y,node->nwChild);
    } else if(isInPixel(x,y,node->neChild)) {
        return getPixel(x,y,node->neChild);
    } else if(isInPixel(x,y,node->swChild)) {
        return getPixel(x,y,node->swChild);
    } else if(isInPixel(x,y,node->seChild)) {
        return getPixel(x,y,node->seChild);
    } else {
        return RGBAPixel();
    }
}

/**
 * isInPixel function
 * @params: int x, y, QuadtreeNode*
 * @return: bool
 * Description:
 * Determines if coordinate is in the given node
 * if x coordinate is greater than or equal to the node's x coordinate, or less than
 * the node's x coordinate + its resolution, than it is within that pixel
 * do the same for y
 */
bool Quadtree::isInPixel(int x, int y, QuadtreeNode* node) const
{
    return (x>=node->x && x<(node->x+node->r)) && (y>=node->y && y<(node->y+node->r));
}

/**
 * decompress function
 * @params: void
 * @return: PNG
 * Description:
 * returns the PNG represented by the Quadtree
 * uses the getPixel function to set the value of the PNG to that of the Quadtree
 */
PNG Quadtree::decompress() const
{
    if(root != NULL) {
        PNG img(root->r,root->r);
        for(int i = 0; i < root->r; i++) {
            for(int j = 0; j < root->r; j++) {
                *(img(i,j)) = getPixel(i,j);
            }
        }
        return img;
    }
    return PNG();
}

/**
 * clockwiseRotate function
 * @params: void
 * @return: void
 * Description:
 * rotates the quadtree
 */
void Quadtree::clockwiseRotate()
{
    return clockwiseRotate(root);
}

/**
 * clockwiseRotate helper function
 * @params: QuadtreeNode*
 * @return: void
 * Description:
 * clockwiseRotate function that actually rotates the quadtree recursively
 * check if node is NULL
 * if not, rotate the x,y coordinates of the pixels,
 * then rotate the actual pixels themselves
 * finally perform the same function on the pixel's children
 */
void Quadtree::clockwiseRotate(QuadtreeNode* node)
{
    if(node->nwChild != NULL) {
        QuadtreeNode* t = node->nwChild;
        node->nwChild = node->swChild;
        node->swChild = node->seChild;
        node->seChild = node->neChild;
        node->neChild = t;

        node->nwChild->x = node->x;
        node->nwChild->y = node->y;
        node->neChild->x = node->x + node->r/2;
        node->neChild->y = node->y;
        node->swChild->x = node->x;
        node->swChild->y = node->y + node->r/2;
        node->seChild->x = node->x + node->r/2;
        node->seChild->y = node->y + node->r/2;

        clockwiseRotate(node->nwChild);
        clockwiseRotate(node->neChild);
        clockwiseRotate(node->swChild);
        clockwiseRotate(node->seChild);
    }
}

/**
 * prune function
 * @params: int
 * @return: void
 * Description:
 * compresses the quadtree that represents a PNG
 */
void Quadtree::prune(int tolerance)
{
    return prune(tolerance,root);
}

/**
 * prune helper function
 * @params: int, QuadtreeNode*
 * @return: void
 * Description:
 * compresses the quadtree that represents a PNG
 * Starts off by checking if the node is null
 * if not null, then check to see if the node is within tolerance
 * check for each subsequent child node as well
 * if not within tolerance, then clear the child nodes and return
 */
void Quadtree::prune(int tolerance, QuadtreeNode* node)
{
    if(node->nwChild != NULL) {
        if(withinTolerance(tolerance, node, node)) {
            clear(node->nwChild);
            clear(node->neChild);
            clear(node->swChild);
            clear(node->seChild);
            return;
        }
        prune(tolerance,node->nwChild);
        prune(tolerance,node->neChild);
        prune(tolerance,node->swChild);
        prune(tolerance,node->seChild);
    }
}

/**
 * withinTolerance function
 * @params: int, QuadtreeNode* origNode, subNode
 * @return: bool
 * Description:
 * determines whether the subnode is within the tolerance of the origNode based on tolerance
 * if node is not NULL, check tolerance of each of child nodes
 */
bool Quadtree::withinTolerance(int tolerance, QuadtreeNode* origNode, QuadtreeNode* subNode) const
{
    if(subNode->nwChild != NULL) {
        return withinTolerance(tolerance,origNode,subNode->nwChild) &&
               withinTolerance(tolerance,origNode,subNode->neChild) &&
               withinTolerance(tolerance,origNode,subNode->swChild) &&
               withinTolerance(tolerance,origNode,subNode->seChild);
    }
    return difference(origNode,subNode) <= tolerance;
}

/**
 * difference helper function
 * @params: QuadtreeNode* origNode and subNode
 * @return: int
 * Description:
 * finds the difference between the RGBAPixel values of origNode and subNode
 */
int Quadtree::difference(QuadtreeNode* origNode, QuadtreeNode* subNode) const
{
    return (origNode->element.red - subNode->element.red)*(origNode->element.red - subNode->element.red) +
           (origNode->element.green - subNode->element.green)*(origNode->element.green - subNode->element.green) +
           (origNode->element.blue - subNode->element.blue)*(origNode->element.blue - subNode->element.blue);
}

/**
 * pruneSize function
 * @params: int
 * @return: int
 * Description:
 * returns the number of leaves that will be pruned by the prune function
 */
int Quadtree::pruneSize(int tolerance) const
{
    return pruneSize(tolerance,root);
}

/**
 * pruneSize helper function
 * @params: int, QuadtreeNode*
 * @return: int
 * Description:
 * actually calculates the value of the pruning instead of actually pruning the tree
 */
int Quadtree::pruneSize(int tolerance, QuadtreeNode* node) const
{
    if(node->nwChild == NULL) {
        return 1;
    }

    if(withinTolerance(tolerance, node, node)) {
        return 1;
    }

    return pruneSize(tolerance, node->nwChild) +
           pruneSize(tolerance, node->neChild) +
           pruneSize(tolerance, node->swChild) +
           pruneSize(tolerance, node->seChild);
}

/**
 * idealPrune function
 * @params: int
 * @return: int
 * Description:
 * calculates the minimum tolerance to guarantee that upon pruning the tree no more than
 * numLeaves remain in Quadtree
 */
int Quadtree::idealPrune(int numLeaves) const
{
    return idealPrune(numLeaves, 0, 200000);
}

/**
 * idealPrune helper function
 * @params: int numLeaves, min, max
 * @return: int
 * Description:
 * calculates the actual value of idealPrune by using the Binary Search method
 *  first start with smallest index and highest index
 *  if numLeaves == average of indexes, subtract average until you hit the minimum
 *  else, if numLeaves is smaller than the index, get the lower bound, else get the higher bound
 */
int Quadtree::idealPrune(int numLeaves, int min, int max) const
{
    if(pruneSize((max+min)/2) == numLeaves) {
        int n = (max+min)/2;
        while(pruneSize(n) == numLeaves) {
            if(pruneSize(n-1) == numLeaves) {
                n--;
            } else {
                break;
            }
        }
        return n;
    } else if(pruneSize((max+min)/2) < numLeaves) {
        return idealPrune(numLeaves,min,(max+min)/2);
    } else {
        return idealPrune(numLeaves,(max+min)/2,max);
    }
}
