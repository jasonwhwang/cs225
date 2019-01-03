/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
    /**
     * Quadtree constructor, creates an empty quadtree
     */ 
    Quadtree();

    /**
     * Quadtree constructor, creates a quadtree with a PNG source file and resolution size
     */ 
    Quadtree(PNG const & source, int resolution);

    /**
     * Quadtree copy constructor, copies another quadtree
     */ 
    Quadtree(Quadtree const & other);

    /**
     * Quadtree destructor, destroys current tree;
     */ 
    ~Quadtree();

    /**
     * Quadtree equal = operator, assign value of tree to another
     */ 
    Quadtree const & operator=(Quadtree const & other);

    /**
     * buildTree creates the tree with a given source file and resolution 
     */ 
    void buildTree(PNG const & source, int resolution);

    /**
     * getPixel gets a pixel from inside of the Quadtree with an x,y coordinate and returns the pixel
     */ 
    RGBAPixel getPixel(int x, int y) const;

    /**
     * decompress returns the PNG represented by the current Quadtree
     */ 
    PNG decompress() const;


    // QUADTREE MODIFICATION FUNCTIONS
    /**
     * clockwiseRotate rotates the PNG represented by the Quadtree by 90 degrees
     */ 
    void clockwiseRotate();

    /**
     * prune compresses the Quadtree that represents a PNG image
     */ 
    void prune(int tolerance);

    /**
     * pruneSize returns the number of leaves that will be pruned by the prune function
     */ 
    int pruneSize(int tolerance) const;

    /**
     * idealPrune size calculates the minimum tolerance necessary to guarantee that upon pruning the tree
     * no more than numLeaves leaves remain in Quadtree
     */ 
    int idealPrune(int numLeaves) const;

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */

        int x, y, r;

        QuadtreeNode(int xval, int yval, int rval)
        {
            nwChild = neChild = swChild = seChild = NULL;
            x = xval;
            y = yval;
            r = rval;
        }

        QuadtreeNode(QuadtreeNode const * node)
        {
            nwChild = node->nwChild;
            neChild = node->neChild;
            swChild = node->swChild;
            seChild = node->seChild;

            element = node->element;

            x = node->x;
            y = node->y;
            r = node->r;
        }
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    /**
     * copy helper function that actually copies the tree
     */ 
    QuadtreeNode* copy(QuadtreeNode* node);
    /**
     * clear helper function that actually clears the memory of the tree
     */ 
    void clear(QuadtreeNode* &node);
    /**
     * buildTree helper function that actually builds the tree
     */ 
    void buildTree(PNG const & source, int resolution, QuadtreeNode* node);

    /**
     * getPixel helper function that actually gets the pixel located at the coordinates
     */
    RGBAPixel getPixel(int x, int y, QuadtreeNode* node) const;
    /**
     * isInPixel is used by the getPixel function to determine whether or not the pixel of interest
     * is inside which child pixel
     */
    bool isInPixel(int x, int y, QuadtreeNode* node) const;
    /**
     * clockwiseRotate helper function that actually rotates the quadtree recursively
     */ 
    void clockwiseRotate(QuadtreeNode* node);
    /**
     * prune helper function that actually prunes the Quadtree based on the tolerance
     */
    void prune(int tolerance, QuadtreeNode* node);
    /**
     * helper function for prune which determines whether or not the values of the pixels are within the tolerance or not
     */
    bool withinTolerance(int tolerance, QuadtreeNode* origNode, QuadtreeNode* subNode) const;
    /**
     * helper function of withinTolerance which finds the difference between the values of the pixels
     */
    int difference(QuadtreeNode* origNode, QuadtreeNode* subNode) const;
    /**
     * prunesize helper function that actually does the prunesizing
     */
    int pruneSize(int tolerance, QuadtreeNode* node) const;
    /**
     * idealPrune helper function that actually calculates the idealPrune value
     */
    int idealPrune(int numLeaves, int min, int max) const;


/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
