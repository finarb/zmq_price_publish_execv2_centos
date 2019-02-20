/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_INTERFACE_CORPORATE_ACTION_H
#define FEEDOS_generated_INTERFACE_CORPORATE_ACTION_H

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "../api/generated_types.h"
#endif

namespace FeedOS {

#define FEEDOS_GEN_DECL_INTERFACE_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_streaming \
		virtual void response_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_Started (); \
		virtual void response_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_Failed (ReturnCode rc); \
		virtual void aborted_CORPORATE_ACTION_DownloadAdjustmentFactorEvents (ReturnCode rc); \
		virtual void notif_AdjustmentFactorEvents	(FeedOS::Types::ListOfAdjustmentFactorEvent const & inEvents); \


	class INTERFACE_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_streaming
	{
	public:
		virtual ~INTERFACE_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_streaming() {}

		virtual void response_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_Started () = 0;
		virtual void response_CORPORATE_ACTION_DownloadAdjustmentFactorEvents_Failed (ReturnCode rc) = 0;
		virtual void aborted_CORPORATE_ACTION_DownloadAdjustmentFactorEvents (ReturnCode rc) = 0;
		virtual void notif_AdjustmentFactorEvents	(FeedOS::Types::ListOfAdjustmentFactorEvent const & inEvents) = 0;

	};
}
#endif
