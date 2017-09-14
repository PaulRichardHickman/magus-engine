#include "scenenode.h"

#include "visitor.h"

namespace MagusEngine
{
	Transform::Transform()
	{
		position.SetX(0.0f);
		position.SetY(0.0f);
		position.SetZ(0.0f);

		rotation.SetX(0.0f);
		rotation.SetY(0.0f);
		rotation.SetZ(0.0f);
				
		scale.SetX(1.0f);
		scale.SetY(1.0f);
		scale.SetZ(1.0f);
	}

	SceneNode::SceneNode()
	{
		_tranform = Transform();

		_material = NULL;
	}
	
	bool SceneNode::Initialise(const char* name, int maxChildren)
	{
		/* Initialise variables */
		_childCount = 0;
		_maxChildCount = maxChildren;
		_componentCount = 0;

		/* Allocate memory for children pointers */
		_children = (SceneNode**)malloc(sizeof(SceneNode**) * maxChildren);

		/* Copy the name */
		strcpy_s(_name, name);

		return true;
	}

	bool SceneNode::InitialiseComponents(int maxComponent)
	{
		/* Initialise variables */
		_componentCount = 0;
		_maxComponentCount = maxComponent;
		
		/* Allocate memory for component pointers */
		_components = (Component**)malloc(sizeof(Component**) * maxComponent);

		return true;
	}

	void SceneNode::Shutdown()
	{
	}

	void SceneNode::AddChild(SceneNode* sceneNode)
	{
		_children[_childCount] = sceneNode;
		_childCount++;
	}

	void SceneNode::AddComponent(Component* component)
	{
		_components[_componentCount] = component;
		_componentCount++;
	}

	void SceneNode::Accept(Visitor* visitor)
	{
		visitor->PreVisit(this);

		visitor->Visit(this);

		for (unsigned int i = 0; i < _componentCount; i++)
		{
			_components[i]->Accept(visitor);
		}

		for (unsigned int i = 0; i < _childCount; i++)
		{
			_children[i]->Accept(visitor);
		}

		visitor->PostVisit(this);
	}

	char* SceneNode::GetName()
	{
		return _name;
	}


	void SceneNode::SetPosition(Vector3f position)	{ _tranform.position = position; }
	void SceneNode::SetRotation(Vector3f rotation)	{ _tranform.rotation = rotation; }
	void SceneNode::SetScale(Vector3f scale)		{ _tranform.scale = scale; }

	void SceneNode::SetPosition(float x, float y, float z) { 
		_tranform.position.SetX(x);
		_tranform.position.SetY(y); 
		_tranform.position.SetZ(z); 
	}

	void SceneNode::SetRotation(float x, float y, float z) { 
		_tranform.rotation.SetX(x);
		_tranform.rotation.SetY(y); 
		_tranform.rotation.SetZ(z); 
	}

	void SceneNode::SetScale(float x, float y, float z) { 
		_tranform.scale.SetX(x);
		_tranform.scale.SetY(y); 
		_tranform.scale.SetZ(z); 
	}

	Vector3f* SceneNode::GetPosition() { return &_tranform.position; }
	Vector3f* SceneNode::GetRotation() { return &_tranform.rotation; }
	Vector3f* SceneNode::GetScale() { return &_tranform.scale; }

	void SceneNode::SetCriticality(bool critical) { _isCritical = critical; }
	bool SceneNode::IsCritical() { return _isCritical; }

	void SceneNode::SetMaterial(Material* material) { _material = material; }
	Material* SceneNode::GetMaterial() { return _material; }
}