<!DOCTYPE html>
<html>
<head>
    <title>Login/Signup</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
    <style>
        body {
            background-color: black;
            color: lime;
        }
        .container {
            margin-top: 50px;
        }
        .hack {
            font-family: 'Hack', monospace;
        }
        .courier {
            font-family: 'Courier New', monospace;
        }
    </style>
    <script>
        function showSignupForm() {
            document.getElementById('loginForm').style.display = 'none';
            document.getElementById('signupForm').style.display = 'block';
        }

        function showLoginForm() {
            document.getElementById('signupForm').style.display = 'none';
            document.getElementById('loginForm').style.display = 'block';
        }

        function validatePassword(password) {
            if(password.length < 5) {
                alert("Password should be at least 5 characters long.");
                return false;
            }
            return true;
        }
    </script>
</head>
<body>
    <div class="container">
        <div id="loginForm">
            <h2 class="hack">Login</h2>
            <form action="login.php" method="post" onsubmit="return validatePassword(document.getElementById('loginPassword').value)">
                <div class="form-group">
                    <label for="loginUsernameEmail">Username or Email</label>
                    <input type="text" class="form-control" id="loginUsernameEmail" name="usernameOrEmail" required>
                </div>
                <div class="form-group">
                    <label for="loginPassword">Password</label>
                    <input type="password" class="form-control" id="loginPassword" name="password" required>
                </div>
                <button type="submit" class="btn btn-primary">Login</button>
                <button type="button" class="btn btn-secondary" onclick="showSignupForm()">Signup</button>
            </form>
        </div>
        <div id="signupForm" style="display: none;">
            <h2 class="courier">Signup</h2>
            <form action="register.php" method="post" onsubmit="return validatePassword(document.getElementById('signupPassword').value)">
                <div class="form-group">
                    <label for="signupUsername">Username</label>
                    <input type="text" class="form-control" id="signupUsername" name="username" required>
                </div>
                <div class="form-group">
                    <label for="signupEmail">Email address</label>
                    <input type="email" class="form-control" id="signupEmail" name="email" required>
                </div>
                <div class="form-group">
                    <label for="signupPassword">Password</label>
                    <input type="password" class="form-control" id="signupPassword" name="password" required>
                </div>
                <button type="submit" class="btn btn-primary">Signup</button>
                <button type="button" class="btn btn-secondary" onclick="showLoginForm()">Login</button>
            </form>
        </div>
    </div>
</body>
</html>

