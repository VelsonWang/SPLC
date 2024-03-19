/*
*   file name:  link_list.h
*   give the opration of link list
*/

#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

	typedef struct tagslList{
		void* pData;
		struct tagslList* pNext;
	}slListNod,*LPslListNod;
	
	typedef struct tsgslListHead{
		LPslListNod pHead;
		long nLen;
	}slListHead,*LPslListHead;

	//����
	void slListInit( slListHead* pHead );								//��ʼ��
	void* slListGetHeapTop( slListHead* pHead, void* pDefaultData );	//��ȡջ��
	int slListPush( slListHead* pHead, void* pData );					//��ջ
	void* slListPop( slListHead* pHead, void* pDefaultData );			//��ջ
	void* slListGetFront( slListHead* pHead, void* pDefaultData );		//��ȡ��ͷ
	void* slListGetRear( slListHead* pHead, void* pDefaultData );		//��ȡ��β
	int slListEnq( slListHead* pHead, void* pData );					//���
	void* slListDeq( slListHead* pHead, void* pDefaultData );			//����
	int slListJumpq( slListHead* pHead, void* pData );					//��ӵ���ͷ

	void* slListGetAt( slListHead* pHead, int nIndex, void* pDefaultData );	//��ȡ��nIndex������
	void slListDeleteAt( slListHead* pHead, int nIndex );
	void slListAddAt( slListHead* pHead, int nIndex, void* pData );
	void slListDelete( slListHead* pHead, void* pData );
	int slListGetLength( slListHead* pHead );
	void slListReMoveAll( slListHead* pHead );
	slListNod* slListGetFistNod( slListHead* pHead );
	slListNod* slListGetNextNod( slListNod* pHead );
	int slListIsHaveData( slListHead* pHead, void* pData );					//�б����Ƿ��������

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif  /* __LINK_LIST_H__ */

