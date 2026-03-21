# ofxBlockGenerator

# 개요

조건에 맞게 무작위로 블록 군집을 생성하여 렌더링합니다.

<img src="https://github.com/han031121/ofxBlockGenerator/blob/main/main_image.jpg" width="500" height="500"/>

### 블록 군집 조건

- 블록 군집의 크기와 블록의 개수는 사용자의 입력으로 제한됩니다.
- 모든 블록들은 아래부터 쌓입니다.
- 블록 군집은 하나의 덩어리로만 이루어져 있습니다.
- 인접한 칸의 더 높은 위치의 블록에 의해 높이를 알 수 없는 부분이 나타나지 않습니다. (기본 시점 기준)

# 개발환경

- Windows 11
- Microsoft Visual Studio 2022
- openframeworks v0.12.1

# 상세설명

### blockData

- 생성자
    - `block_count_1`, `block_count_2` : 블록 개수의 범위를 정합니다.
    - `max_r`, `max_c`, `max_h` : 각각 최대 행, 최대 열, 최대 높이를 정합니다.
    - `density = 25` : 블록이 뭉쳐서 생성되는 정도를 정합니다.
    - `allow_duplicate = 0` : 이미 생성된 모양에 대해 중복 생성 허가 여부를 정합니다.
- `generateBlock()` : `blockData` 객체 내부에 블록 군집 데이터를 생성합니다.
- `get~~` : 특정 변수를 반환합니다
    - `getData(r, c, h)` : r, c, h 좌표의 블록 존재 여부
    - `getHeightData(r,c)` : r, c 좌표의 높이
    - `getMaxRow()`, `getMaxCol()`, `getMaxHeight()` : 행, 열, 높이의 최댓값
    - `getSizeRow()`, `getSizeCol()`, `getSizeHeight()` : 현재 생성된 데이터의 행, 열, 높이의 크기
    - `getCenter()` : 블록 군집의 정 중앙 좌표
    - `getBlockCount()` : 현재 생성된 데이터의 블록 개수
- `isGenerated()` : 블록 군집의 생성 여부를 반환합니다.
- `getIdentify()` : 현재 생성된 데이터의 고유문자열을 반환합니다.

### drawObject

- 생성자
    - `data` : 출력하고자 하는 `blockData` 객체를 정합니다.
    - `width`, `height` : 출력 이미지의 크기를 정합니다.
    - `degree_xz = 25`, `degree_h = 20` : 카메라의 각도를 정합니다.
    - `light_degree_xz = 25`, `light_degree_h = 38` : 광원의 각도를 정합니다.
    - `thickness = 2` : 윤곽선의 굵기를 정합니다.
- `render()` : 객체 내부에 이미지를 생성합니다.
- `saveImage()` : 객체 내부에 생성된 이미지를 파일로 저장합니다.
- `getImage()` : 객체 내부의 이미지를 ofImage로 저장합니다.
- `getPixels()` : 객체 내부의 이미지를 ofPixels로 저장합니다.
- `~~Update` : 특정 변수를 변경합니다.
    - `camDegreeUpdate(deg_xz, deg_h, isRelative)` : 카메라 각도
    - `lightDegreeUpdate(deg_xz, deg_h, isRelative)` : 광원 각도
    - `blockColorUpdate(r, g, b, isRelative` : 블록 색
    - `camDistUpdate(d, isRelative)` : 카메라 거리
    
    `isRelative` 옵션이 `true`인 경우, 현재 값에서 입력된 값 만큼 변화시킵니다.
    
- `get~~` : 특정 변수를 반환합니다.
    - `getCamDegreeXZ()`
    - `getCamDegreeH()`
    - `getLightDegreeXZ()`
    - `getLightDegreeH()`
    - `getblockColor()`
    - `getCamDist()`
- `drawFbo()` : 내부에 생성된 이미지를 화면에 출력합니다.
- `getIdentify()` : 현재 이미지의 고유문자열을 반환합니다.

# 사용방법

1. `blockData` 객체를 생성합니다.
2. `blockData`의 `generateBlock` 함수를 실행하여 블록 군집 데이터를 생성합니다.
3. 생성된 `blockData` 객체를 기반으로 `drawObject` 객체를 생성합니다.
4. `drawObject`의 `render` 함수로 렌더링하고, `drawFbo` 함수로 화면에 이미지를 출력합니다.

자세한 사용방법은 example 프로젝트를 참고해주세요.

# 주의사항

- 중복 생성 방지 옵션을 선택한 경우, 크기가 큰 군집에 대해서 후반부에 성능 저하가 우려됩니다.
- 중복 생성 방지 옵션을 선택한 경우, 아직 생성되지 않은 모양이 존재함에도 불구하고 생성이 중단될 가능성이 있습니다.
- 생성하는 이미지의 해상도는 고정되어 있습니다.
- 앞의 블록에 가려져 높이를 알 수 없는 부분이 존재할 수 있습니다.
