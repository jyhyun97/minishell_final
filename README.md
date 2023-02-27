# minishell

<img width="569" alt="minishell" src="https://user-images.githubusercontent.com/72776427/221513584-09e8b24f-bad9-47b5-b28b-53f6e4a04ab0.png">

## 요구사항

bash와 똑같이 동작하는 프로그램을 C로 작성하기.

몇개의 빌트인 명령어(echo, pwd, cd 등)는 직접 구현하기.

리다이렉션(<, <<, >, >>) 및 파이프(|) 구현.

환경변수 구현.

## 구현 과정 요약

readline 라이브러리와 execve(), pipe()등을 사용.

[bash parser](https://mywiki.wooledge.org/BashParser)를 참조해 입력 받은 문자열을 파싱.

1. 토큰화 : 문자열을 의미가 있는 최소한의 단위로 분해.
2. lexicalize : 토큰에 의미 부여.
3. 파싱 : 실행가능한 단위로 토큰 묶기.

‘, “, $ 등 특수한 경우의 예외처리.

자식 프로세스부터 명령어를 실행해 부모에 실행결과를 전달하는 멀티 파이프를 만들기.

빌트인 함수(echo, pwd, cd, env, export, unset) 구현.

## 기타

2인 팀과제로 페어프로그래밍을 사용해 작성되었음.
