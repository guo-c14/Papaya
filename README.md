# Papaya

C++ Path Tracer (路径追踪器) 

## 概要

### 渲染算法

- Uniformly Distributed Path Tracing

### 实现特性

- Anti-aliasing
- 软阴影
- Material
	- Diffuse
	- Metal
	- Dielectrics
	- 通用材料模型（可自定义漫反射、镜面反射、折射的参数）
- Texture
	- 棋盘
	- uv贴图
	- 环境光贴图
- 景深
- 运动模糊
- 高次贝塞尔曲线旋转曲面
- 复杂网格读写
- BVH（AABB）
- 多线程

## 效果

### 漫反射

![](Outputs/Diffuse.ppm)

### 镜面反射

![](Outputs/Metal.ppm)

### 折射和相机视角转换

![](Outputs/Camera.ppm)

### 焦散（景深）

![](Outputs/Defocus.ppm)

### 随机场景

![](Outputs/Random.ppm)

### 运动模糊

![](Outputs/Motion.ppm)

### 棋盘纹理

![](Outputs/Texture.ppm)

### Cornell Box

![](Outputs/CornellBox.ppm)

### 贝塞尔曲线（四次）旋转面

![](Outputs/Bezier.ppm)

### Others

![](Outputs/Others.ppm)

### 网格模型

![](Outputs/dragon.ppm)

### Cornell Box + Dragon + 景深

![](Outputs/DragonCornell.ppm)

### 贝塞尔曲线旋转面 + 环境光贴图 + 网格模型 + 景深

![](Outputs/BezierCurve.ppm)

![](Outputs/bezier_curve.ppm)