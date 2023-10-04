#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char pathname[64];
    unsigned char ptitle[64];
    unsigned char pico[64];
    unsigned char rhomepageURL[32];
    unsigned char default_text[256];
    unsigned char isTemplate;
    unsigned char isViewable;
    unsigned char showNavbar;  // New field
} page_data_t;

// Function prototypes
static void start_menu(page_data_t *page);
static void write_library(const char* filename, const char* content);
static void write_page(page_data_t *page);
void main_menu(void);
void generate_default_website(void);

static void make_default_librarys()
{
    printf("Creating default libraries...\n");

    // Write the library file
    write_library("website_figure.php", "<?php\n"
    "session_start();\n"
    "if (!isset($_SESSION['id'])) {\n"
    "    $_SESSION['id'] = uniqid();\n"
    "}\n"
    "function write_header($title) {\n"
    "    $currentPage = basename($_SERVER['PHP_SELF']);\n"
    "    echo '<head>';\n"
    "    echo '<title>' . $title . '</title>';\n"
    "    echo '<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">';\n"
    "    echo '<style>';\n"
    "    echo '.navbar { background-color: black; }';\n"
    "    echo '.navbar a { color: lime; }';\n"
    "    echo '.active { background-color: lime; color: black; }';\n"
    "    echo '</style>';\n"
    "    echo '</head>';\n"
    "    echo '<body>';\n"
    "    echo '<nav class=\"navbar navbar-expand-lg navbar-dark bg-dark\">';\n"
    "    echo '<button class=\"navbar-toggler\" type=\"button\" data-toggle=\"collapse\" data-target=\"#navbarNav\" aria-controls=\"navbarNav\" aria-expanded=\"false\" aria-label=\"Toggle navigation\">';\n"
    "    echo '<span class=\"navbar-toggler-icon\"></span>';\n"
    "    echo '</button>';\n"
    "    echo '<div class=\"collapse navbar-collapse\" id=\"navbarNav\">';\n"
    "    echo '<ul class=\"navbar-nav\">';\n"
    "    echo '<li class=\"nav-item ' . ($currentPage == 'default1.php' ? 'active' : '') . '\">';\n"
    "    echo '<a class=\"nav-link\" href=\"default1.php\">Default 1</a>';\n"
    "    echo '</li>';\n"
    "    echo '<li class=\"nav-item ' . ($currentPage == 'default2.php' ? 'active' : '') . '\">';\n"
    "    echo '<a class=\"nav-link\" href=\"default2.php\">Default 2</a>';\n"
    "    echo '</li>';\n"
    "    echo '<li class=\"nav-item ' . ($currentPage == 'default3.php' ? 'active' : '') . '\">';\n"
    "    echo '<a class=\"nav-link\" href=\"default3.php\">Default 3</a>';\n"
    "    echo '</li>';\n"
    "    echo '</ul>';\n"
    "    echo '</div>';\n"
    "    echo '</nav>';\n"
    "}\n"
    "function write_footer() {\n"
    "    echo '<footer>';\n"
    "    echo '<p>Copyright &copy; 2022 Your Website</p>';\n"
    "    echo '</footer>';\n"
    "}\n"
    "function write_form($action, $method) {\n"
    "    echo '<form action=' . $action . ' method=' . $method . ' class=\"form-horizontal\">';\n"
    "    echo '<div class=\"form-group\">';\n"
    "    echo '<label for=fname>First name:</label><br>';\n"
    "    echo '<input type=text id=fname name=fname class=\"form-control\"><br>';\n"
    "    echo '</div>';\n"
    "    echo '<div class=\"form-group\">';\n"
    "    echo '<label for=lname>Last name:</label><br>';\n"
    "    echo '<input type=text id=lname name=lname class=\"form-control\"><br><br>';\n"
    "    echo '</div>';\n"
    "    echo '<input type=submit value=Submit class=\"btn btn-primary\">';\n"
    "    echo '</form>';\n"
    "}\n"
    "?>");

    // Write the second library file
    write_library("website_security.php", "<?php\n"
    "function sanitize_input($data) {\n"
    "    return filter_var($data, FILTER_SANITIZE_STRING);\n"
    "}\n"
    "function prevent_xss($data) {\n"
    "    if (preg_match('/<a>|<xss>/i', $data)) {\n"
    "        die('Potential XSS attack detected.');\n"
    "    }\n"
    "    return htmlspecialchars($data, ENT_QUOTES, 'UTF-8');\n"
    "}\n"
    "function use_prepared_statements($pdo, $sql, $parameters) {\n"
    "    $stmt = $pdo->prepare($sql);\n"
    "    $stmt->execute($parameters);\n"
    "    return $stmt;\n"
    "}\n"
    "function implement_csp() {\n"
    "    header(\"Content-Security-Policy: default-src 'self'\");\n"
    "}\n"
    "function use_http_only_cookies() {\n"
    "    ini_set('session.cookie_httponly', 1);\n"
    "}\n"
    "?>");

    printf("Default libraries created.\n");
}

// Function definitions
static void start_menu(page_data_t *page) {
    printf("Starting menu...\n");

    printf("Enter a title for your page: ");
    fgets(page->ptitle, sizeof(page->ptitle), stdin);

    printf("Enter the path to your page icon: ");
    fgets(page->pico, sizeof(page->pico), stdin);

    printf("Enter the URL for your homepage: ");
    fgets(page->rhomepageURL, sizeof(page->rhomepageURL), stdin);

    printf("Enter some default text for your page: ");
    fgets(page->default_text, sizeof(page->default_text), stdin);

    printf("Is this a template page? (1 for yes, 0 for no): ");
    scanf("%hhu", &page->isTemplate);

    printf("Is this page viewable? (1 for yes, 0 for no): ");
    scanf("%hhu", &page->isViewable);

    printf("Menu completed.\n");
}

// Function to write content to a file
static void write_to_file(const char* filename, const char* content) {
    printf("Writing to file...\n");

    if (filename == NULL || content == NULL) {
        printf("E-0x001: Invalid arguments.\n");
        return;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("E-0x001: Failed to open file for writing");
        return;
    }

    fprintf(fp, "%s", content);
    fclose(fp);
    fp = NULL;

    printf("File written.\n");
}

// Function to write a library
static void write_library(const char* filename, const char* content) {
    printf("Writing library...\n");
    write_to_file(filename, content);
    printf("Library written.\n");
}

// Function to write a page
static void write_page(page_data_t *page) {
    printf("Writing page...\n");
    // TODO: Add code to generate page content based on page data
    char page_content[2048] = {0};  // Adjust size as needed
    sprintf(page_content, "<?php\n");
    if (page->showNavbar) {
        strcat(page_content, "include 'website_figure.php';\n");
    }
    sprintf(page_content + strlen(page_content), "write_header('%s');\n", page->ptitle);
    strcat(page_content, "echo '<body>';\n");
    sprintf(page_content + strlen(page_content), "echo '<h1>%s</h1>';\n", page->ptitle);
    if (page->isTemplate) {
        strcat(page_content, "write_form('submit.php', 'post');\n");
    }
    strcat(page_content, "echo '</body>';\n");
    strcat(page_content, "write_footer();\n");
    strcat(page_content, "?>\n");
    write_to_file(page->pathname, page_content);
    printf("Page written.\n");
}

void generate_default_website() {
    // Generate library files
    make_default_librarys();

    // Create page_data_t structures for default pages
    page_data_t page1 = {"default1.php", "Default 1", "icon1.ico", "http://www.default1.com", "Default text 1", 1, 1, 1};
    page_data_t page2 = {"default2.php", "Default 2", "icon2.ico", "http://www.default2.com", "Default text 2", 1, 1, 1};
    page_data_t page3 = {"default3.php", "Default 3", "icon3.ico", "http://www.default3.com", "Default text 3", 1, 1, 1};

    // Generate default pages
    write_page(&page1);
    write_page(&page2);
    write_page(&page3);

    char *index_content = "<!DOCTYPE html>\n"
                      "<html>\n"
                      "<head>\n"
                      "<meta charset=\"UTF-8\">\n"
                      "<title>Welcome</title>\n"
                      "<link href=\"https://fonts.googleapis.com/css2?family=Hack:wght@400;700&display=swap\" rel=\"stylesheet\">\n"
                      "<style>\n"
                      "body {\n"
                      "    background-color: black;\n"
                      "    color: lime;\n"
                      "    font-family: 'Hack', monospace;\n"
                      "}\n"
                      "h1, h2 {\n"
                      "    text-align: center;\n"
                      "    color: lime;\n"
                      "    text-shadow: 0 0 20px lime, 0 0 30px lime, 0 0 40px lime;\n"
                      "}\n"
                      "p {\n"
                      "    color: red;\n"
                      "    text-align: center;\n"
                      "    font-size: 20px;\n"
                      "}\n"
                      "img {\n"
                      "    display: block;\n"
                      "    margin-left: auto;\n"
                      "    margin-right: auto;\n"
                      "    width: 50%;\n"
                      "}\n"
                      "section {\n"
                      "    margin: 50px;\n"
                      "}\n"
                      "</style>\n"
                      "</head>\n"
                      "<body>\n"
                      "<h1>Welcome to our website!</h1>\n"
                      "<p><a href='loginsignup.php'>Login or Sign up</a> to continue</p>\n"
                      "<section>\n"
                      "<h2>About Us</h2>\n"
                      "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed euismod, nisl id varius congue, neque purus pellentesque dolor, a eleifend risus justo sit amet enim.</p>\n"
                      "<img src=\"server_image.jpg\" alt=\"Server Image\">\n"
                      "</section>\n"
                      "<section>\n"
                      "<h2>Contact Us</h2>\n"
                      "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed euismod, nisl id varius congue, neque purus pellentesque dolor, a eleifend risus justo sit amet enim.</p>\n"
                      "<img src=\"wires_image.jpg\" alt=\"Wires Image\">\n"
                      "</section>\n"
                      "<section>\n"
                      "<h2>Our Mission</h2>\n"
                      "<p>The website is going under development to achieve community programming and community support results.</p>\n"
                      "<img src=\"anonymous_mask_image.jpg\" alt=\"Anonymous Mask Image\">\n"
                      "</section>\n"
                      "</body>\n"
                      "</html>\n";

    char *signuplogin_content = "";
    write_to_file("loginsignup.php", signuplogin_content);

    write_to_file("index.php", index_content);
}

void main_menu() {
    printf("Starting main menu...\n");

    int choice;
    page_data_t page;
    memset(&page, 0, sizeof(page_data_t));  // Zero out memory

    printf("1. Generate a new page\n");
    printf("2. Write a new library\n");
    printf("3. Generate default website\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            start_menu(&page);
            write_page(&page);
            break;
        case 2:
            // TODO: Add code to gather user input for library filename and content
            char filename[64] = {0};
            char content[256] = {0};
            printf("Enter the filename for your library: ");
            scanf("%s", filename);
            printf("Enter the content for your library: ");
            scanf("%s", content);
            write_library(filename, content);
            break;
        case 3:
            generate_default_website();
            break;
        default:
            printf("Invalid choice. Please enter 1, 2 or 3.\n");
            main_menu();
            break;
    }

    printf("Main menu completed.\n");
}

int main() {
    main_menu();
    return 0;
}
