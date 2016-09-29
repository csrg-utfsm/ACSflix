//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#ifndef PUBLISHER_SCOPEDREF_H
#define PUBLISHER_SCOPEDREF_H

/**
 * Scoped "smart pointer" for Backwards compatibility
 */
template <typename T>
class ScopedRef
{
	T * m_ref;

public:
	ScopedRef(T * ref) :
			m_ref(ref)
	{
	}

	~ScopedRef()
	{
		delete m_ref;
	}

	T * operator->()
	{
		return m_ref;
	}
};


#endif //PUBLISHER_SCOPEDREF_H
