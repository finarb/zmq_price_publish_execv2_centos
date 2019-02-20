
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_PDU_TOOLS_H
#define FEEDOS_COMM_PDU_TOOLS_H

namespace FeedOS {

	unsigned int const PDU_ID_ENCODING_BITS				= 32;
	unsigned int const PDU_ID_ENCODING_SERVICE_BITS		= 14;
	unsigned int const PDU_ID_ENCODING_OPERATION_BITS	= 10;
	unsigned int const PDU_ID_ENCODING_TYPE_BITS		= 8;
	unsigned int const PDU_ID_ENCODING_TYPE_POS			= 0;
	unsigned int const PDU_ID_ENCODING_OPERATION_POS	= PDU_ID_ENCODING_TYPE_POS+PDU_ID_ENCODING_TYPE_BITS;
	unsigned int const PDU_ID_ENCODING_SERVICE_POS		= PDU_ID_ENCODING_OPERATION_POS+PDU_ID_ENCODING_OPERATION_BITS;
	unsigned int const PDU_ID_ENCODING_FULL_MASK		= (unsigned int)~0;
	unsigned int const PDU_ID_ENCODING_SERVICE_MASK		= PDU_ID_ENCODING_FULL_MASK << PDU_ID_ENCODING_SERVICE_POS;
	unsigned int const PDU_ID_ENCODING_TYPE_MASK		= PDU_ID_ENCODING_FULL_MASK >> (PDU_ID_ENCODING_BITS-PDU_ID_ENCODING_TYPE_BITS);
	unsigned int const PDU_ID_ENCODING_OPERATION_MASK	= PDU_ID_ENCODING_FULL_MASK & ~(PDU_ID_ENCODING_SERVICE_MASK) & ~(PDU_ID_ENCODING_TYPE_MASK);
	inline unsigned int MAKE_PDU_ID(unsigned int TYPE,unsigned int SRV,unsigned int OPERATION)
	{
		return ( (TYPE << PDU_ID_ENCODING_TYPE_POS) | (SRV << PDU_ID_ENCODING_SERVICE_POS) | (OPERATION  << PDU_ID_ENCODING_OPERATION_POS) );
	}
	inline unsigned int MAKE_PDU_ID_SIBLING(unsigned int TYPE,unsigned int PDUID)
	{
		return ( (TYPE << PDU_ID_ENCODING_TYPE_POS) | ((PDUID) & ~ PDU_ID_ENCODING_TYPE_MASK) );
	}
	inline unsigned int GET_PDU_TYPE(unsigned int PDUID)
	{
		return ( (PDUID & PDU_ID_ENCODING_TYPE_MASK) >> PDU_ID_ENCODING_TYPE_POS );
	}
	inline unsigned int GET_PDU_SERVICE(unsigned int PDUID)
	{
		return ( (PDUID & PDU_ID_ENCODING_SERVICE_MASK) >> PDU_ID_ENCODING_SERVICE_POS );
	}
	inline unsigned int GET_PDU_OPERATION(unsigned int PDUID)
	{
		return ( (PDUID & PDU_ID_ENCODING_OPERATION_MASK) >> PDU_ID_ENCODING_OPERATION_POS );
	}

	typedef enum {
		PDU_Type_Request			= 0,
		PDU_Type_SubscribeRequest	= 1,		
		PDU_Type_UnsubscribeRequest	= 2,
		PDU_Type_Response			= 3,
		PDU_Type_SubscribeResponse	= 4,
		PDU_Type_SubscribeNotif		= 5,
		PDU_Type_UnsubscribeNotif	= 6
	} PDU_Type;

}


#endif
