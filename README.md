# os-assignment-UCO


sendto() :
하부 프로토콜을 이용하여 어플리케이션 데이터를 보내는 함수. 
데이터를 보낼때 지역 IP 주소와 포트번호가 결정되지 않은 상태이면 시스템이 자동으로 결정한다.
암시적인 bind() 역할을 한다.

sendto() :

The sendto function sends data to a specific destination.

int sendto(
  SOCKET         s, 
  const char     *buf,
  int            len,
  int            flags,
  const sockaddr *to,
  int            tolen
);

s) A descriptor identifying a (possibly connected) socket.
*buf) A pointer to a buffer containing the data to be transmitted.
len) The length, in bytes, of the data pointed to by the buf parameter.
*to)flags) A set of flags that specify the way in which the call is made.
tolen) An optional pointer to a sockaddr structure that contains the address of the target socket.


첫번째 인자) 통신을 위한 소켓
두번째 인자) 보낼 데이터를 담는 버퍼의 주소
세번째 인자) 보낼 데이터의 크기
네번째 인자) 함수의 동작을 바꾸는 옵션, 대부분 0
다섯째 인자) 목적지 주소를 담고있는 소켓 주소 구조체 변수의 포인터
UPD는 다자간 통신이 용이하기때문에 브로드캐스트나 멀티케스트 주소를 사용할 수도 있다.
여섯째 인자) 소켓 주소 구조체의 크기

UDP 소켓에는 송신버퍼가 존재하지 않으므로, sendto() 가 리턴을 하더라도 실제로 데이터 전송이 완료된 뜻도 아니며, 상대방이 받았는지 확인할 수도 없다.
sendto() 함수로 보낸 데이터는 UDP 데이터그램(패킷)으로 만들어지며, 수신측에서는 한번의 recvfrom() 함수로 데이터를 읽는다. : 메시지 경계 구분 작업을 어플리케이션 단에서 할 필요가 없음.
UDP 소켓에 대해 sendto()함수로 한번에 보낼 수 있는 데이터의 최대 크기는 65535 - IP 헤더 크기(20) - UDP 헤더 크기(8) 이다.
블로킹 소켓은 커널(운영체제) 영역에 복사할공간이 부족하면 sendto() 함수 호출시 블록된다. 
UDP 클라이언트에서 sendto() 사용 예시) 

recvfrom() :

수신 버퍼에 도착한 데이터를 어플리케이션 버퍼로 복사하는 역할을 하는 함수.

recv() 함수와의 차이점 : 한번에 하나의 UDP 데이터만 읽을 수 있다. 버퍼를 크게 잡아도 많은 데이터를 한꺼번에 읽지 못한다.

int recvfrom( SOCKET s, char* buf, int len, int flags, struct sockaddr* from, int* fromlen );

첫번째 인자) 통신을 위한 소켓

두번째 인자) 받은 데이터를 저장할 버퍼의 주소

세번째 인자) 버퍼의 크기, 읽어야할 크기가 더 크면 나머지 데이터는 버린다.

네번째 인자) 함수의 동작을 바꾸는 옵션, 대부분 0.

다섯째 인자) 송신자의 소켓 주소 구조체 변수의 포인터

여섯째 인자) 다섯째인자가 가리키는 메모리 영역의 크기로 초기화 한 후 변수의 포인터를 넣는다. 함수가 리턴하면 함수가 초기화한 메모리크기값을 갖게된다. 값-결과 인자

sendto() 함수로 보낸 데이터는 UDP 데이터그램(패킷)으로 만들어지며, 수신측에서는 한번의 recvfrom() 함수로 데이터를 읽는다. : 메시지 경계 구분 작업을 어플리케이션 단에서 할 필요가 없음.
TCP 소켓에서는 recvfrom() 의 리턴값이 0일경우 정상종료를 의미하지만, UDP 소켓에서는 연결종료를 의미하는것이 아니다.
블로킹 소켓의 경우 도달한 데이터가 없으면 recvfrom() 함수 호출시 블록된다. 
