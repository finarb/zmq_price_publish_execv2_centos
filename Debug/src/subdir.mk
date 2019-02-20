################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MarketSheetClient_base.cpp \
../src/MarketSheetClient_text.cpp \
../src/SyntheticOrderBook.cpp \
../src/init_trace.cpp \
../src/perform_async_snapshot.cpp \
../src/perform_dl_and_sub_histo_intraday_extended.cpp \
../src/perform_download_intraday_bars_ext.cpp \
../src/perform_get_generic_tag_by_source_id.cpp \
../src/perform_getticksizetables.cpp \
../src/perform_gettradeconditions.cpp \
../src/perform_histo_daily_ext.cpp \
../src/perform_histo_intraday.cpp \
../src/perform_histo_newsdownload.cpp \
../src/perform_market_status.cpp \
../src/perform_newslookup.cpp \
../src/perform_price_instrument.cpp \
../src/perform_quotdownload.cpp \
../src/perform_refdownload.cpp \
../src/perform_refdownload_and_subscribe.cpp \
../src/perform_refget.cpp \
../src/perform_reflookup.cpp \
../src/perform_refstructure.cpp \
../src/perform_resolvecodes.cpp \
../src/perform_snapshot.cpp \
../src/perform_subscribe.cpp \
../src/perform_subscribe_L1.cpp \
../src/perform_subscribe_L1_by_MIC.cpp \
../src/perform_subscribe_L2_by_MIC.cpp \
../src/perform_subscribe_MBL.cpp \
../src/perform_subscribe_MBO.cpp \
../src/perform_subscribe_NEWS.cpp \
../src/perform_subscribe_feed_status.cpp \
../src/perform_subscribe_instruments_MBO.cpp \
../src/perform_subscribe_oneMBL.cpp \
../src/perform_subscribe_oneMBL_and_mergeLayers.cpp \
../src/simple_observer.cpp \
../src/tools.cpp 

OBJS += \
./src/MarketSheetClient_base.o \
./src/MarketSheetClient_text.o \
./src/SyntheticOrderBook.o \
./src/init_trace.o \
./src/perform_async_snapshot.o \
./src/perform_dl_and_sub_histo_intraday_extended.o \
./src/perform_download_intraday_bars_ext.o \
./src/perform_get_generic_tag_by_source_id.o \
./src/perform_getticksizetables.o \
./src/perform_gettradeconditions.o \
./src/perform_histo_daily_ext.o \
./src/perform_histo_intraday.o \
./src/perform_histo_newsdownload.o \
./src/perform_market_status.o \
./src/perform_newslookup.o \
./src/perform_price_instrument.o \
./src/perform_quotdownload.o \
./src/perform_refdownload.o \
./src/perform_refdownload_and_subscribe.o \
./src/perform_refget.o \
./src/perform_reflookup.o \
./src/perform_refstructure.o \
./src/perform_resolvecodes.o \
./src/perform_snapshot.o \
./src/perform_subscribe.o \
./src/perform_subscribe_L1.o \
./src/perform_subscribe_L1_by_MIC.o \
./src/perform_subscribe_L2_by_MIC.o \
./src/perform_subscribe_MBL.o \
./src/perform_subscribe_MBO.o \
./src/perform_subscribe_NEWS.o \
./src/perform_subscribe_feed_status.o \
./src/perform_subscribe_instruments_MBO.o \
./src/perform_subscribe_oneMBL.o \
./src/perform_subscribe_oneMBL_and_mergeLayers.o \
./src/simple_observer.o \
./src/tools.o 

CPP_DEPS += \
./src/MarketSheetClient_base.d \
./src/MarketSheetClient_text.d \
./src/SyntheticOrderBook.d \
./src/init_trace.d \
./src/perform_async_snapshot.d \
./src/perform_dl_and_sub_histo_intraday_extended.d \
./src/perform_download_intraday_bars_ext.d \
./src/perform_get_generic_tag_by_source_id.d \
./src/perform_getticksizetables.d \
./src/perform_gettradeconditions.d \
./src/perform_histo_daily_ext.d \
./src/perform_histo_intraday.d \
./src/perform_histo_newsdownload.d \
./src/perform_market_status.d \
./src/perform_newslookup.d \
./src/perform_price_instrument.d \
./src/perform_quotdownload.d \
./src/perform_refdownload.d \
./src/perform_refdownload_and_subscribe.d \
./src/perform_refget.d \
./src/perform_reflookup.d \
./src/perform_refstructure.d \
./src/perform_resolvecodes.d \
./src/perform_snapshot.d \
./src/perform_subscribe.d \
./src/perform_subscribe_L1.d \
./src/perform_subscribe_L1_by_MIC.d \
./src/perform_subscribe_L2_by_MIC.d \
./src/perform_subscribe_MBL.d \
./src/perform_subscribe_MBO.d \
./src/perform_subscribe_NEWS.d \
./src/perform_subscribe_feed_status.d \
./src/perform_subscribe_instruments_MBO.d \
./src/perform_subscribe_oneMBL.d \
./src/perform_subscribe_oneMBL_and_mergeLayers.d \
./src/simple_observer.d \
./src/tools.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTARGET_PLATFORM_LINUX -I"/home/abhishek/Documents/Repos/TradingApplication/Price_Publisher/FEEDOS/zmq_price_publish_execv1/api/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


