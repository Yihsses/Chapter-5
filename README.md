# Documentation

使用 `make` 工具來編譯並生成執行檔：

- `make fcfs` 生成 `fcfs` 執行檔
- `make sjf` 生成 `sjf` 執行檔
- `make rr` 生成 `rr` 執行檔
- `make priority` 生成 `priority` 執行檔
- `make priority_rr` 生成 `priority_rr` 執行檔

---

# Example
## Input File (`input.txt`):
```plaintext
P1, 2, 2
P2, 5, 6
P3, 0, 4
P4, 0, 7
P5, 7, 4
P6, 10, 40
```

執行 `make fcfs` 來編譯並運行 `fcfs` 排程演算法：

```bash
make fcfs
./fcfs input.txt
```

### Output:
(在此插入執行結果)
