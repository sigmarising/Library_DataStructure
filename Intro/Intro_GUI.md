# 图形化版本 v1.0 beta

## 交互说明

1.  用户进入主界面
    *   切换计时方式
    *   登陆
    *   更换主题
    *   天数手动推进(前提已切换手动计时)

2.  登陆
    *   管理员
        *   新建书
        *   新建人
        *   查找书
        *   查找人
        *   更改密码
        *   登出 返回1
    *   用户
        *   借书/预约
        *   还书
        *   转换
        *   还款
        *   更改密码
        *   登出 返回1

> 我们认为一个人系统在线的时间不可能跨越两天，因为没人会在图书馆过夜（除了管理员）。所以我们的计时操作只可能在无用户登入时才进行

## 窗体说明 - Dialog

### 窗体编号

1.  DMain1 & DMain2 - 自动计时主界面 & 手动计时主界面
2.  DMainC - 计时方式切换主界面
3.  DColor - 更换颜色界面
4.  DLogin - 登陆界面
5.  DAdmin - 管理员主界面
6.  DAdmin_NBook1 - 管理员新建图书界面1
7.  DAdmin_NBook2 - 管理员新建图书界面2
8.  DAdmin_NPerson - 管理员新建用户界面
9.  DAdmin_FBook - 管理员查书界面
10. DAdmin_FPerson1 - 管理员查用户界面
11. DAdmin_FPerson2 - 管理员查用户详细界面
12. DUser - 用户界面
13. DUser_Borrow - 用户借书界面
14. DUser_Return - 用户还书界面
15. DUser_Convert - 用户预约转借阅界面
16. DUser_Key - 用户更改密码界面
17. DAdmin_FPerson2 - 管理员查书详细界面
18. DAdmin_Key - 管理员密码更改界面

> 由于设计时功能遗漏 导致查人详细界面的编号靠后

### 窗体切换

以下文字代表的含义  
例如:  
    1 -> 2 3 4  
表示界面1可以切换到界面2 3 4

窗体编号切换说明：

    1 -> 2 3 4
    2 -> 1
    3 -> 1
    4 -> 5 12
    5 -> 6 8 9 10 18
    6 -> 5 7
    7 -> 5
    8 -> 5
    9 -> 5 17
    17 -> 5
    10 -> 5 11
    11 -> 5
    12 -> 4 13 14 15 16
    13 -> 12
    14 -> 12
    15 -> 12
    16 -> 12
    18 -> 5

### 使用简介

初始时使用管理员账号登陆（账号和密码都是`Admin`）

接下来使用管理员账号进行添加人、添加书操作

以上操作成功后，可以使用成功添加的人账号进行登陆