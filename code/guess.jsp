<%@page import="java.util.Random"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>数字猜谜游戏</title>
    </head>
    <body>
        <jsp:useBean id="guess" class="Gu.GuessNumber" scope="session" />
        
        <%-- 只在会话中没有 answer 的时候才生成随机数 --%>
        <%
            if (guess.getAnswer() == 0) { 
                Random randomNumbers = new Random();
                int answer = 1 + randomNumbers.nextInt(100);
                guess.setAnswer(answer);  // 将生成的随机数存储在会话中
            }
        %>

        <h3>系统已生成了一个1到100之间的随机整数，请猜是什么数？</h3>
        <hr>

        <form action="Guess.jsp" method="get">
            <label for="guessNumber">输入你的猜的数: </label>
            <input type="text" id="guessNumber" name="guessNumber" required>
            <input type="submit" value="提交">
        </form>

        <hr>

        <%-- 设置和获取猜测数据 --%>
        <jsp:setProperty name="guess" property="guessNumber" param="guessNumber"/>
        <jsp:getProperty name="guess" property="result"/>
        <p>你猜的数字是：<jsp:getProperty name="guess" property="guessNumber"/>。</p>
        <p>这是第 <jsp:getProperty name="guess" property="guessCount"/> 次猜。</p>

        <%-- 如果猜对了，显示正确答案并给出重新开始的链接 --%>
        <% if (guess.isRight()) { %>
            <p>恭喜你，猜对了！答案是 <jsp:getProperty name="guess" property="answer"/>。</p>
            <a href="<%= response.encodeRedirectURL("Guess.jsp") %>">重新开始游戏</a>
        <% } else { %>
            <p>答案是 <jsp:getProperty name="guess" property="answer"/>，你还没有猜对。继续加油！</p>
        <% } %>
        
        <hr>
        <a href="<%= response.encodeRedirectURL("getNumber.jsp") %>">重新开始猜数</a>
    </body>
</html>
