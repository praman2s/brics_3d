/******************************************************************************
* BRICS_3D - 3D Perception and Modeling Library
* Copyright (c) 2011, GPS GmbH
*
* Author: Sebastian Blumenthal
*
*
* This software is published under a dual-license: GNU Lesser General Public
* License LGPL 2.1 and Modified BSD license. The dual-license implies that
* users of this code may choose which terms they prefer.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License LGPL and the BSD license for
* more details.
*
******************************************************************************/

#ifndef RSG_SCENEGRAPHFACADE_H
#define RSG_SCENEGRAPHFACADE_H

#include "ISceneGraphQuery.h"
#include "ISceneGraphUpdate.h"
#include "ISceneGraphUpdateObserver.h"
#include "IIdGenerator.h"
#include "Group.h"
#include "Node.h"
#include "Transform.h"
#include "UncertainTransform.h"
#include "GeometricNode.h"
#include "Shape.h"

#include <map>
#include <boost/weak_ptr.hpp>
using std::map;


//namespace brics_3d { namespace rsg { class Attribute; }  }
//namespace brics_3d { class WorldModel; }
//namespace brics_3d { namespace rsg { class IIdGenerator; }  }

namespace brics_3d {

namespace rsg {

/**
 * @brief The central handle to create and maintain a robot scenegraph. It holds the root node of the scene graph.
 *
 * The SceneGraphFacade takes care (maintains consistency) of mapping between IDs and internal pointers.
 * The implemented interfaces allow to create and maintain a scengraph bases on the node IDs only.
 *
 * @ingroup sceneGraph
 */
class SceneGraphFacade : public ISceneGraphQuery, public ISceneGraphUpdate {

  public:
	SceneGraphFacade();

    SceneGraphFacade(IIdGenerator* idGenerator);

    virtual ~SceneGraphFacade();

    /* Facade specific methods */
    unsigned int getRootId();

    /* Implemented query interfaces */
    bool getNodes(vector<Attribute> attributes, vector<unsigned int>& ids); //subgraph?
    bool getNodeAttributes(unsigned int id, vector<Attribute>& attributes);
    bool getNodeParents(unsigned int id, vector<unsigned int>& parentIds);
    bool getGroupChildren(unsigned int id, vector<unsigned int>& childIds);
    bool getTransform(unsigned int id, TimeStamp timeStamp, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr& transform);
    bool getUncertainTransform(unsigned int id, TimeStamp timeStamp, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr& transform, ITransformUncertainty::ITransformUncertaintyPtr &uncertainty);
    bool getGeometry(unsigned int id, Shape::ShapePtr& shape, TimeStamp& timeStamp);

    bool getTransformForNode (unsigned int id, unsigned int idReferenceNode, TimeStamp timeStamp, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr& transform);

    /* Implemented update interfaces */
    bool addNode(unsigned int parentId, unsigned int& assignedId, vector<Attribute> attributes, bool forcedId = false);
    bool addGroup(unsigned int parentId, unsigned int& assignedId, vector<Attribute> attributes, bool forcedId = false);
    bool addTransformNode(unsigned int parentId, unsigned int& assignedId, vector<Attribute> attributes, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform, TimeStamp timeStamp, bool forcedId = false);
    bool addUncertainTransformNode(unsigned int parentId, unsigned int& assignedId, vector<Attribute> attributes, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform, ITransformUncertainty::ITransformUncertaintyPtr uncertainty, TimeStamp timeStamp, bool forcedId = false);
    bool addGeometricNode(unsigned int parentId, unsigned int& assignedId, vector<Attribute> attributes, Shape::ShapePtr shape, TimeStamp timeStamp, bool forcedId = false);
    bool setNodeAttributes(unsigned int id, vector<Attribute> newAttributes);
    bool setTransform(unsigned int id, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform, TimeStamp timeStamp);
    bool setUncertainTransform(unsigned int id, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform, ITransformUncertainty::ITransformUncertaintyPtr uncertainty, TimeStamp timeStamp);
	bool deleteNode(unsigned int id);
    bool addParent(unsigned int id, unsigned int parentId);
    bool removeParent(unsigned int id, unsigned int parentId);

    /* Configuration */
    bool attachUpdateObserver(ISceneGraphUpdateObserver* observer);
    bool detachUpdateObserver(ISceneGraphUpdateObserver* observer);

    /* Coordination methods */
	bool executeGraphTraverser(INodeVisitor* visitor, unsigned int subgraphId);

  private:

	/// Internal initiaization.
    void initialize();

    /**
     * @brief Resolved IDs to references.
     * @param id The ID.
     * @return The reference. Will be NULL in case no reference could be found.
     */
    Node::NodeWeakPtr findNodeRecerence(unsigned int id);

    /**
     * @brief Test if an ID is in the idLookUpTable.
     * @param id The ID.
     * @return True if ID is in table, otherwise false.
     */
    bool doesIdExist(unsigned int id);

    /// The root of all evil...
    Group::GroupPtr rootNode;

    /// Table that maps IDs to references.
    map<unsigned int, Node::NodeWeakPtr > idLookUpTable;

    /// Iterator for idLookUpTable
    map<unsigned int, Node::NodeWeakPtr >::const_iterator nodeIterator;

    /// Handle to ID generator. Can be optionally specified at creation.
    IIdGenerator* idGenerator;

    /// Set of observers that will be notified when the update function will be called.
    std::vector<ISceneGraphUpdateObserver*> updateObservers;


};

} // namespace brics_3d::rsg

} // namespace brics_3d
#endif

/* EOF */

