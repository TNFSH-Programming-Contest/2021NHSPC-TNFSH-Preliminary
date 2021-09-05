# GAMAGAMA

\begin{figure}[h]
\centering
\includegraphics[width=12cm]{cover.jpg}
\caption{風花向遊客解說海洋生物，出自動畫《白沙的Aquatope》}
\end{figure}

GAMAGAMA水族館面臨即將停業的危機，代理館長空空琉決定推出觸摸池的活動來吸引遊客，由前偶像團體成員的風花擔任導覽員。  
觸摸池吸引了不少家長帶著小孩來參觀，風花推出了有獎徵答，答對的小朋友累積積分來兌換獎品。  
而空空琉為了炒熱氣氛，決定加碼讓遊客的積分能夠翻倍。  

GAMAGAMA水族館有兩條觀察大型水族箱的海底隧道，空空琉會在海底隧道中沿路擺上調整積分的告示牌，遊客要選擇其中一條隧道參觀，每走過一面告示牌，就會按照告示牌上的內容對目前的積分進行修改。  
例如你目前的積分是 $x$，則經過 $+a$ 的告示牌時，積分就會變成 $x+a$；經過 $\times a$的告示牌時，積分就會變成 $x \times a$。積分的修改是經過告示牌後立即運算更新，不是四則運算。  

為了控制不要讓積分過度膨脹，必須先進行模擬。  
一開始兩條隧道都是沒有擺放任何告示牌，隨著活動進行，會不斷在其中一條隧道的尾端加上一面告示牌。  
要模擬的變動及詢問請見輸入說明。  

\clearpage

## 輸入
第一行有一個數字 $Q$，表示接下來的操作次數。  
接下來有 $Q$ 行，每一行為操作為以下其一（皆不含引號）。  

 - "`1 k`" --- 若遊客進入隧道前的積分為 $k$，請輸出經過兩條隧道後的積分較大值。
 - "`2 i + a`" --- 在 $i$ 號隧道最尾端加上 $+a$ 的告示牌。
 - "`2 i * a`" --- 在 $i$ 號隧道最尾端加上 $\times a$ 的告示牌。
 - "`3`" --- 輸出當下遊客無論選擇哪條隧道，最終積分皆相同的初始積分，若不存在或多組解則輸出 "`no`"（不含引號）。

## 輸出
對於每筆操作 $1$ 請輸出一個整數 $k$。  
對於每筆操作 $3$ 請輸出一個整數 $k$ 或 "`no`"（不含引號）。  

## 輸入限制
 - $1 \leq Q \leq 10^6$
 - 操作 $1$ 中 $-10000 \leq k \leq 10000$
 - 操作 $2$ 中 $i \in \{1, 2\}$ 且 $-100 \leq a \leq 100$
 - 保證若初始積分符合 $-10000 \leq k \leq 10000$ ，則無論選擇哪條隧道，任何時間手上的積分都在 $[-10^9, 10^9]$ 之內。

## 子任務
\subtasks

\clearpage

## 範例輸入 1
```
8
1 3
2 1 + 2
1 3
2 2 * 2
1 3
2 1 + 2
1 3
3
```

## 範例輸出 1
```
3
5
6
7
4
```

## 範例說明 1
\begin{tabular}{m{.5em} m{0.44\textwidth} m{.5em} m{0.44\textwidth}}
	&
	\includegraphics[width=0.39\textwidth]{s1-img0.png} &
	$\Rightarrow$ &
	\includegraphics[width=0.39\textwidth]{s1-img1.png} \\
\end{tabular}
\begin{tabular}{m{.5em} m{0.44\textwidth} m{.5em} m{0.44\textwidth}}
	&
	(一開始兩條隧道沒有告示牌) \newline
	操作 1：\enskip $3\quad[\max(3,\ 3) = 3]$
	&
	&
	操作 2：\enskip 隧道1接上 $+ 2$ \newline
	操作 3：\enskip $5\quad[\max(3+2,\ 3) = 5]$
	\\
\end{tabular}

\begin{tabular}{m{.5em} m{0.44\textwidth} m{.5em} m{0.44\textwidth}}
	$\Rightarrow$ &
	\includegraphics[width=0.39\textwidth]{s1-img2.png} &
	$\Rightarrow$ &
	\includegraphics[width=0.39\textwidth]{s1-img3.png} \\
\end{tabular}
\begin{tabular}{m{.5em} m{0.44\textwidth} m{.5em} m{0.44\textwidth}}
	&
	操作 4：\enskip 隧道2接上 $\times 2$ \newline
	\mbox{操作 5：\enskip $6\quad[\max(3+2,\ 3 \times 2) = 6]$}
	&
	&
	操作 6：\enskip 隧道1接上 $+ 2$ \newline
	\mbox{操作 7：\enskip $7\quad[\max(3+2+2,\ 3 \times 2) = 7]$} \newline
	操作 8：\enskip $4\quad[4+2+2 = 4 \times 2 = 8]$
	\\
\end{tabular}
\clearpage

## 範例輸入 2
```
9
1 3
2 1 * 0
1 3
3
2 2 * 0
1 3
3
2 1 + 2
3
```

## 範例輸出 2
```
3
3
0
0
no
no
```

## 範例說明 2
\begin{tabular}{m{.5em} m{0.44\textwidth} m{.5em} m{0.44\textwidth}}
	&
	\includegraphics[width=0.39\textwidth]{s2-img0.png} &
	$\Rightarrow$ &
	\includegraphics[width=0.39\textwidth]{s2-img1.png} \\
\end{tabular}
\begin{tabular}{m{.5em} m{0.44\textwidth} m{.5em} m{0.44\textwidth}}
	&
	(一開始兩條隧道沒有告示牌) \newline
	操作 1：\enskip $3\quad[\max(3,\ 3) = 3]$
	&
	&
	操作 2：\enskip 隧道1接上 $\times 0$ \newline
	操作 3：\enskip $3\quad[\max(3 \times 0,\ 3) = 3]$ \newline
	操作 4：\enskip $0\quad[0 \times 0 = 0 = 0]$
	\\
\end{tabular}

\clearpage

\begin{tabular}{m{.5em} m{0.44\textwidth} m{.5em} m{0.44\textwidth}}
	$\Rightarrow$ &
	\includegraphics[width=0.39\textwidth]{s2-img2.png} &
	$\Rightarrow$ &
	\includegraphics[width=0.39\textwidth]{s2-img3.png} \\
\end{tabular}
\begin{tabular}{m{.5em} m{0.44\textwidth} m{.5em} m{0.44\textwidth}}
	&
	操作 5：\enskip 隧道2接上 $\times 0$ \newline
	\mbox{操作 6：\enskip $0\quad[\max(3 \times 0,\ 3 \times 0) = 0]$}
	\mbox{操作 7：\enskip $\text{no}\quad[\text{多組解}]$}
	&
	&
	操作 8：\enskip 隧道1接上 $+ 2$ \newline
	\mbox{操作 9：\enskip $\text{no}\quad[\text{不存在}]$}
	\\
\end{tabular}