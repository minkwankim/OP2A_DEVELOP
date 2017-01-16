//
//  gridCFD.hpp
//  OP2A
//
//  Created by Kim M.K. on 11/01/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#ifndef gridCFD_hpp
#define gridCFD_hpp

#include <stdio.h>
#include "../DATA/dataCFD.hpp"
#include "../GRID/grid.hpp"


/*
namespace CFD {
    
    // 1. Class for Node
    class Node : public NodeNormal<dataCFDbasic>
    {
        // Part A: Data section
    public:
        
        // Part B: Constructor and Destructor Section
    public:
        Node() {};
        ~Node() {};
        
        // Part C: Class function section
    public:
        
    };
    
    
    // 2. Class for Face
    class Face : public FaceNormal<dataCFDbasic>
    {
        // Part A: Data section
    public:
        
        // Part B: Constructor and Destructor Section
    public:
        Face() {};
        ~Face() {};
        
        // Part C: Class function section
    public:
    };
    
    
    // 3. Class for Cell
    namespace  EXPLICIT
    {
        class Cell : public CellNormal<dataCFD>
        {
            // Part A: Data section
        public:
            
            // Part B: Constructor and Destructor Section
        public:
            Cell() {};
            ~Cell() {};
            
            // Part C: Class function section
        public:
        };
    }
    
    namespace IMPLICIT
    {
        class Cell : public CellNormal<dataCFD2>
        {
            // Part A: Data section
        public:
            
            // Part B: Constructor and Destructor Section
        public:
            Cell() {};
            ~Cell() {};
            
            // Part C: Class function section
        public:
        };
    }
}
*/

/*
namespace CFDCART {
    
    // 1. Class for Node
    class Node : public NodeCart<dataCFDbasic>
    {
        // Part A: Data section
    public:
        
        // Part B: Constructor and Destructor Section
    public:
        Node() {};
        ~Node() {};
        
        // Part C: Class function section
    public:
        
    };
    
    
    // 2. Class for Face
    class Face : public FaceCart<dataCFDbasic>
    {
        // Part A: Data section
    public:
        
        // Part B: Constructor and Destructor Section
    public:
        Face() {};
        ~Face() {};
        
        // Part C: Class function section
    public:
    };
    
    
    // 3. Class for Cell
    namespace  EXPLICIT
    {
        class Cell : public CellCart<dataCFD>
        {
            // Part A: Data section
        public:
            
            // Part B: Constructor and Destructor Section
        public:
            Cell() {};
            ~Cell() {};
            
            // Part C: Class function section
        public:
        };
    }
    
    namespace IMPLICIT
    {
        class Cell : public CellCart<dataCFD2>
        {
            // Part A: Data section
        public:
            
            // Part B: Constructor and Destructor Section
        public:
            Cell() {};
            ~Cell() {};
            
            // Part C: Class function section
        public:
        };
    }
}
 
 */


class Node;
int test(Node* node1, Node* node2);



#endif /* gridCFD_hpp */
