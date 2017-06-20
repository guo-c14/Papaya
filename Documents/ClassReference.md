## Camera类

> 依赖Ray.hpp

### protected 成员

#### 变量

Type|Name|Meaning
:---:|:---:|:---:
Vec3D|c|透镜中心
Vec3D|u|透镜平面横轴单位向量
Vec3D|v|透镜平面纵轴单位向量
Vec3D|o|视平面的左下原点
Vec3D|x|视平面横轴向量，长度为左边到右边
Vec3D|y|视平面纵轴向量，长度为底边到上边
double|lens_radius|透镜半径
double|exposure_start_time|曝光开始时间
double|exposure_stop_time|曝光结束时间

### public 成员

#### 函数

Return Type|Name|Meaning
:---:|:---:|:---:
-|Camera|构造函数
Ray|emitRay|发射一条采样光线
