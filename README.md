# **이슈 확인 필요!!**
# MiniRT
- 파싱부 처리
    - info 구조체에 파싱해온 정보들, mlx, 움직일 물체 정보가 들어있음
    - 에러 처리
        - rgb는 int로만 받도록 처리
        - rgb값 0 ~ 255 처리
        - 숫자 뒤에 문자 오는거, 숫자 사이에 문자 오는거 처리
        - 파일 확장자명 처리
        - 라인별 인자 개수 처리
        - 백터값 -1 ~ 1 처리
        - 중복 식별자(A, C, L) 처리
        - ratio(AMB, light) 0 ~ 1 처리
- 구현부 처리
    - 파싱 이후 mlx init, mlx 에러 처리
    - 카메라 정보 바탕으로 뷰포트 구함 (뷰포트는 광선 쏠때 걔 좌표 구하려고 필요함)
        - ex) 임의의 x, y 좌표에 광선 쏘면 광선의 백터는 뷰포트 왼쪽 하단으로부터 x, y만큼 떨어진 지점과 카메라를 잇는 직선
    - 광선 방향 구하고 광선 발사 -> 부딪히는 물체가 있는지 확인 (info의 list를 돌면서 t_obj로 형변환 후 type 확인)
        - 부딪힐 때마다 방정식 통해 t값, 부딪히는 점의 좌표, 부딪히는 점의 좌표의 법선 계산. t값 계속 갱신됨(0 이상의 작은 값으로)
    - pong 조명 모델 적용 -> 색의 강도 구하는 부분이 대부분
        - 일단 그림자 안에 있는지 확인
            - 부딪힌 점의 좌표와 광원의 백터 차이를 구함
            - 부딪힌 점의 좌표로부터 광원까지 광선 발사
            - 걸리는 지점 있으면 그림자로 처리
        - 난반사 적용
            - 법선과 광선 cos 값 기반으로 한 kd값 구함
            - kd값 바탕으로 빛의 양 정함
        - 정반사 적용
            - 바라보는 방향 백터 구함
            - 반사 백터 구함
            - 둘의 차이가 적으면 반짝인다...!(spec 값 계산)
            - spec, ks(광택 정도) 값으로 실질적인 색 구함
        - 난반사 + 정반사 + 주변광 적용
        - 여기서 구한 색의 강도에 실제 색을 적용시킴
        - (추가) 해당 점이 물체의 표면에 있으면 반쯤 어둡게 해서 내보냄
- MLX 이벤트 부분 
    - 기타 처리(ESC, X표 종료)
    - 물체 선택
        - 마우스 클릭 시 해당 좌표를 가지고 물체 hit 여부 판단
        - hit한 물체를 info의 clicked에 저장
        - clicked가 NULL이 아니라면 방향키로 이동 가능
        - 클릭할 수 없는 카메라, 광원은 각각 키보드 (C - 카메라, L - 광원) 키로 선택
    - 물체 이동
        - 선택된 물체를 이동시킴
        - 카메라 방향에 따라 보이는 그대로 이동
        - A : 왼쪽 방향
        - S : 화면 방향
        - W : 화면에서 멀어지는 방향
        - D : 오른쪽 방향
        - Q : 위로 이동
        - E : 아래로 이동
    - 물체 회전
        - 왼쪽 화살표 : y축 방향 회전
        - 오른쪽 화살표 : y축 방향 회전
        - 위쪽 화살표 : x축 방향 회전
        - 아래쪽 화살표 : x 방향 회전
        - Z : z축 방향 회전
        - X : z축 방향 회전
    - 물체 크기 변경
        - ] : 크기 증가
        - [ : 크기 감소
