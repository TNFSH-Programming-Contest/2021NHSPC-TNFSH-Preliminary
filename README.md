# TPS範例題目

## Quick Links

| ID | gen | solution | tests | statement | validator | config |
| --- | --- | --- | --- | --- | --- | --- |
| A. Arithmetic | [gen](Arithmetic/gen) | [solution](Arithmetic/solution) [check](Arithmetic/solution/check.txt) | [tests](Arithmetic/tests) | [statement](Arithmetic/statement) [problem](Arithmetic/statement/problem.md) | [validator](Arithmetic/validator) |[problem](Arithmetic/problem.json) [solutions](Arithmetic/solutions.json) [subtasks](Arithmetic/subtasks.json) |

# 操作說明
## 題目設定、[problem.json](Arithmetic/problem.json)
| 參數 | 範例值 | 設定位置 |
| --- | --- | --- |
| 競賽名稱 | TPS範例題目 | [problem.json](Arithmetic/problem.json)的`contest_name`欄位（所有題目皆需設定） |
| 題目編號 | A | [problem.json](Arithmetic/problem.json)的`problem_label`欄位 |
| 題目代號 | Arithmetic | [problem.json](Arithmetic/problem.json)的`name`和`code`欄位 |
| 題目名稱 | 四則運算 | [problem.json](Arithmetic/problem.json)的`title`欄位 |
| 時間限制 | 1 秒 | [problem.json](Arithmetic/problem.json)的`time_limit`欄位 |
| 記憶體限制 | 512 MB | [problem.json](Arithmetic/problem.json)的`memory_limit`欄位 |
| 上傳間隔 | 120 秒 | [problem.json](Arithmetic/problem.json)的`min_submission_interval`欄位 |

## 題本、[statement/](Arithmetic/statement/)
題本使用Markdown撰寫並置於[statement/problem.md](Arithmetic/statement/problem.md)，格式請參照該連結。  
切到題目目錄底下後使用`tps statement`指令產生PDF檔。

## 子任務配分、[subtasks.json](Arithmetic/subtasks.json)
子任務配分設定於[subtasks.json](Arithmetic/subtasks.json)。格式如下範例：  
```json
{
    "global_validators": ["validator.cpp"],
    "subtasks": {
        "task1": {
            "index": 1,
            "score": 40,
            "validators": []
        },
        "task2": {
            "index": 2,
            "score": 60,
            "validators": ["validator-2.cpp"]
        }
    }
}
```
`subtasks`底下的Key為各測資名稱（如`task1`），`score`為該測資的分數。  

## 產生測資、[gen/](Arithmetic/gen/)、[gen/data](Arithmetic/gen/data)
產生測資的程式應置於[gen/](Arithmetic/gen/)下。  
以下說明適用於符合TPS產測方式的作法。  
產測程式根據**命令行參數**來產生不同測資，該程式產生測資必須使用**標準輸出（stdout）**，不能是檔案輸出。  
在[gen/data](Arithmetic/gen/data)設定各子任務所使用的程式名稱及參數。  
每一行代表一個測資點，使用`@subtask 測資名稱`區分不同子任務，測資名稱不可有空白，並且應跟`subtasks.json`內相同。範例如下：  
``` 
@subtask sample
manual sample-01.in

@subtask a0
gen task2 qutxm

@subtask 1e4
gen norm 0 10000 csizh

@subtask all
manual all-01.in
gen norm -1000000000 1000000000 jvnyj
```
如果需要手動產生測資，將測資檔放置於[gen/manual](Arithmetic/gen/manual)，然後在`gen/data`寫入一行`manual 測資檔名稱`。  
切到題目目錄底下後使用`tps gen`指令產生測資檔於[tests](Arithmetic/tests)。  

## 驗測程式、[validator/](Arithmetic/validator/)
驗證測資**數值範圍**、圖論題是否為一棵樹、是否連通等題目所給定的限制（與解題演算法無關）屬於驗測程式範疇，放置於[validator/](Arithmetic/validator/)資料夾下。  
並在[subtasks.json](Arithmetic/subtasks.json)設定要使用哪個驗測程式。  
所有子任務都使用的設定於`subtasks.json`的`global_validators`。  
單一子任務使用的則設定於對應子任務下的`validators`。  

測試不同演算法**是否會TLE、得到哪些部分分數**的程式應視為**標程**，請參閱標程說明。  

## 標程、[solutions/](Arithmetic/solutions/)、[solutions.json](Arithmetic/solutions.json)
將標程及其他拿部分分的解法都放在[solutions/](Arithmetic/solutions/)底下。  
並在[solutions.json](Arithmetic/solutions.json)設定標程如以下格式：  
```json
{
	"filename.cpp": {
		"verdict": "model_solution"
	}
}
```
其他解法是否設定於`solutions.json`皆無所謂。  
`verdict`值可參閱[官方說明](https://github.com/ioi-2017/tps/tree/master/docs#solutionsjson)。  

## [checker/](Arithmetic/checker/)
因為TPS沒有提供CMS所使用的white-diff checker，本範例提供完全相符比較的checker（比CMS嚴格），該檔案不會匯入到CMS中（務必使用[TFcis/cms](https://github.com/TFcis/cms)及在`problem.json`中設定`"ignore_checker": true`）。  

## 資料夾結構
每題中包含以下目錄和檔案：
 - checker: 檢查輸出與標準答案是否相等的程式
 - gen: 所有產測資相關的程式碼，參見[TPS的說明](https://github.com/ioi-2017/tps/tree/master/docs#gen)
 - gen/data: 測資產生指令，參見[TPS的說明](https://github.com/ioi-2017/tps/tree/master/docs#gendata)
 - scripts: TPS所使用的腳本
 - solution: 標程及其他解法程式碼（包含所有拿部分分的程式碼），不要跟 validator 搞混
 - solution/check.txt: 所有標程對於所有測資的執行狀況（包含是否WA、TLE）
 - statement: 題本
 - statement/problem.md: （TPS格式）markdown 格式的題目敘述，之後會以 pandoc 輸出成 PDF
 - statement/problem.pdf: （TPS格式）用 `tps statement` 輸出的 PDF 題目敘述
 - tests: 測試資料
 - tests/mapping: 各子任務所屬測資檔案對應表（`tps gen` 自動產生），使用於自動匯入CMS時
 - validator: 驗證測資格式是否正確，是否符合範圍限制，各子任務是否符合各自限制，不要跟 solution 搞混
 - problem.json: 題目設定，包含時限及CMS設定
 - solutions.json: 標程設定，用以產生輸出檔的標程參數為 `"verdict": "model_solution"`
 - subtasks.json: 子任務分數設定
