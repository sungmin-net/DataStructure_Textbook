#ifndef _SIM_DEF_
#define _SIM_DEF_

typedef enum SimStatusType {
    ARRIVAL,
    START,
    END
} SimStatus;

typedef struct SimCustomerType {
    SimStatus status;
    int arrivalTime;    // 도착시간
    int serviceTime;    // 서비스 시간
    int startTime;      // 서비스 시작 시간
    int endTime;        // 종료 시간 : 시작 + 서비스 시간
} SimCustomer;

#endif
