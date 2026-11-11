# 修复 xmake CI：包安装确认在无交互终端下失败

## 失败信息
- Run 42442002013（C/C++ CI）`xmake -y` 步骤：
  `please input: (y/n/m)` 后
  `error: packages(linenoise): must be installed!` → exit 255

## 原因分析
- workflow 中 `xmake f -m debug`（configure）会触发依赖包 linenoise 的安装确认提示；
  该命令没有带 `-y`，CI 无 stdin，确认读到 EOF 被判为拒绝 → 包未安装直接报错。
  `-y` 只加在了后续的 `xmake -y`（build）上，没加到 configure 上。

## 修复内容
- `.github/workflows/*.yml`：`xmake f -m debug` → `xmake f -m debug -y`。

## 验证记录
| Run | 结果 |
|---|---|
| 新 push 触发 run | 待填 |
| 42442002013 (re-run, 修复前) | failure — configure 无 -y |
