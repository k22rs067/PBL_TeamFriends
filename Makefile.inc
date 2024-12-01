APPL_COBJS += 

APPL_CXXOBJS += RearMotor.o \
                EV3ColorSensor.o \
                LineTraceAction.o \
				RunParameter.o \
                Action.o \
                Display.o \
                Button.o \
                ArmControl.o \
                RunStraightAction.o \
                CalcCurrentLocation.o \
                DistanceJudgement.o \
                LapSectionTactics.o \
                RotateAction.o \
                RotateMachineAction.o \
                Tactics.o \
                ArmPositionSetAction.o \
                FreeAreaTactics.o \

SRCLANG := c++


ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
include $(EV3RT_SDK_LIB_DIR)/lib2/Makefile

endif
