# pD.Title
給長度 $N$ 的\textbf{正整數}數列 $a$，求一區間使「區間和 $\text{mod } K$」最大。

註: 先 $\text{mod } K$ 後再比較大小，即 $\displaystyle\max_{1 \leq L \leq R \leq N}{\left[\left(\sum_{i=L}^{R}{a_i}\right)\mod K\right]}$。

## 範圍
- $1 \leq N \leq 2 \cdot 10^6$
- $1 \leq K \leq 10^9$
- $1 \leq a_i \leq 10^9$

## 輸入
第一行有 $2$ 個正整數 $N$, $K$。\
第二行有 $N$ 個正整數 $a_i$。

## 輸出
輸出最大的「區間和 $\text{mod } K$」。

## 子任務
\subtasks

\clearpage

## 範例輸入 1
```
5 5
1 1 1 1 1
```

## 範例輸出 1
```
4
```

## 範例輸入 2
```
7 11
3 3 5 7 7 8 8
```

## 範例輸出 2
```
8
```

## 範例輸入 3
```
5 5
1 2 3 2 1
```

## 範例輸出 3
```
4
```