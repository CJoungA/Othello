# Othello

Unreal Engine 4.27과 C++로 구현한 네트워크 오셀로 게임입니다.  
호스트가 방을 열고 클라이언트가 IP로 접속해 2인이 같은 보드 상태를 공유하며 플레이할 수 있도록 구성했습니다.

## Play Video

[![Othello gameplay video](https://img.youtube.com/vi/C9QNxuP1WHM/maxresdefault.jpg)](https://youtu.be/C9QNxuP1WHM)

> 이미지를 클릭하면 플레이 영상으로 이동합니다.

## Project Summary

| 항목 | 내용 |
| --- | --- |
| 장르 | 보드게임 / 멀티플레이 |
| 개발 환경 | Unreal Engine 4.27 |
| 주요 기술 | C++, UMG, Listen Server, RPC, GameState Replication |
| 플레이 방식 | 호스트 생성 후 클라이언트 IP 접속 |
| 핵심 구현 | 오셀로 규칙 판정, 유효 수 표시, 턴 제한 시간, 승패 판정, 네트워크 동기화 |

## Key Features

- **2인 네트워크 플레이**
  - 호스트는 Listen Server로 게임 맵을 열고, 클라이언트는 IP 입력으로 접속합니다.
  - 서버가 플레이어 입력 위치를 받아 모든 클라이언트에 전달해 동일한 보드 상태를 유지합니다.

- **오셀로 룰 구현**
  - 8방향 탐색으로 유효한 착수 위치를 계산합니다.
  - 돌을 놓은 뒤 뒤집어야 하는 상대 돌을 찾아 색을 갱신합니다.
  - 둘 수 있는 칸을 초록색으로 표시해 플레이 흐름을 쉽게 파악할 수 있습니다.

- **게임 진행 UI**
  - 보드 크기와 턴 제한 시간을 입력해 게임을 시작할 수 있습니다.
  - 흰 돌/검은 돌 개수를 실시간으로 표시합니다.
  - 제한 시간이 끝나면 턴이 자동으로 넘어갑니다.
  - 보드가 가득 차거나 한쪽 돌이 없어지면 승패 또는 무승부를 표시합니다.

- **턴 기반 입력 제어**
  - 현재 플레이어의 턴이 아닐 때는 클릭 입력을 무시합니다.
  - 호스트와 클라이언트의 턴을 분리해 잘못된 입력을 방지했습니다.

## Implementation Highlights

### Network Flow

1. 호스트가 `HostServer()`를 호출해 `GameMap`을 Listen Server로 엽니다.
2. 클라이언트는 `JoinServer()`에서 입력한 IP 주소로 접속합니다.
3. 플레이어가 유효한 칸을 클릭하면 `BTestServer()`로 서버에 위치 인덱스를 전달합니다.
4. 서버는 접속 중인 모든 컨트롤러에 `BTestClient()`를 호출합니다.
5. 각 클라이언트는 `ApplyNetworkMove()`로 같은 수를 적용해 보드 상태를 갱신합니다.

### Game Logic

- `IsCheckMakeMap()`  
  현재 턴의 돌이 특정 칸에 놓일 수 있는지 8방향으로 검사합니다.

- `StoneReverse()`  
  착수 위치를 기준으로 뒤집을 수 있는 상대 돌을 찾아 현재 턴의 돌로 변경합니다.

- `GameSet()`  
  매 턴마다 유효 수를 다시 계산하고, 클릭 가능한 칸만 활성화합니다.

- `GameOverSet()`  
  돌 개수와 보드 상태를 기준으로 승리/패배/무승부를 판정합니다.

## Code Structure

```text
Source/Othello/
├─ ServerMenuController.*   # 호스트/접속 처리, RPC 기반 입력 동기화
├─ ServerMenuWidget.*       # 서버 생성, IP 접속, 종료 UI
├─ MainMenuWidget.*         # 보드 크기/턴 시간 입력 및 게임 시작 UI
├─ PlayGameWidget.*         # 보드 생성, 오셀로 룰, 턴/타이머/승패 처리
├─ ButtonWidget.*           # 보드 칸 UI와 돌 상태 관리
├─ OthelloStateBase.*       # 보드 크기, 타이머, 선택 위치 등 GameState 복제 데이터
└─ OthelloGameModeBase.*    # 접속 플레이어 위젯 전환 흐름 관리
```

## How To Run

1. Unreal Engine 4.27에서 `Othello.uproject`를 엽니다.
2. 프로젝트 파일 생성 후 빌드합니다.
3. 호스트 플레이어는 `Host Game`을 선택합니다.
4. 클라이언트 플레이어는 호스트 IP를 입력하고 `Join Game`을 선택합니다.
5. 보드 크기와 턴 제한 시간을 입력한 뒤 게임을 시작합니다.

## What To Watch In The Video

- 호스트와 클라이언트가 같은 게임 보드를 공유하는지
- 현재 턴에서 둘 수 있는 칸만 표시되는지
- 착수 후 양쪽 화면에서 돌 뒤집기 결과가 동일하게 반영되는지
- 돌 개수, 턴 제한 시간, 게임 종료 문구가 정상적으로 갱신되는지


