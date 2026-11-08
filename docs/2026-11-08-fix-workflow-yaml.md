# 修复记录：workflow 文件解析失败导致 startup_failure（2026-11-08）

## 失败信息
- 仓库：wiseism/ctestlinenoise
- Workflow：.github/workflows/c-cpp.yml
- 失败 run：[42411561199](https://github.com/wiseism/ctestlinenoise/actions/runs/42411561199)（2026-11-07）

## 现象
- run 名称直接显示为文件路径 `.github/workflows/c-cpp.yml`，无任何 job；
- run 日志下载 404（jobs 数为 0）。

## 原因分析
workflow 属 startup_failure。`run: |` 块标量中间夹了两行**顶格注重新解**
```
#        xmake build ctestttbox_list2
#        xmake run ctestttbox_list2
```
顶格注解行于块标量内部不合规（本地 pyyaml 复现：
`while parsing a block mapping ... expected <block end>, but found '<scalar>'`），
GitHub Actions 解析失败后整个 workflow 无法创建 job。

另外原文件为 CRLF 行尾，一并规范化为 LF。

## 修复内容
- 删除 `run: |` 块内的两行顶格注解；
- 文件行尾 CRLF → LF。
（本地 `yaml.safe_load` 通过）

## 验证
| run id | 结果 |
| --- | --- |
| 本次推送触发 | 待填 |
