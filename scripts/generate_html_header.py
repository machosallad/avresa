import os

def convert_html_to_cpp_string_literal(html_file_path, output_file_path):
    with open(html_file_path, 'r') as html_file:
        html_content = html_file.read()

    cpp_string_literal = 'const char index_html[] PROGMEM = R"rawliteral(\n' + html_content + '\n)rawliteral";\n'

    with open(output_file_path, 'w') as output_file:
        output_file.write('#ifndef INDEX_HTML_H\n')
        output_file.write('#define INDEX_HTML_H\n\n')
        output_file.write('#include <Arduino.h>\n\n')
        output_file.write(cpp_string_literal)
        output_file.write('\n#endif // INDEX_HTML_H\n')

def pre_build_action(source, target, env):
    print("Generate index_html.h from index.html")
    html_file_path = 'data/index.html'
    output_file_path = 'lib/web_server/src/index_html.h'
    convert_html_to_cpp_string_literal(html_file_path, output_file_path)

if __name__ == "__main__":
    html_file_path = 'data/index.html'
    output_file_path = 'lib/web_server/src/index_html.h'
    convert_html_to_cpp_string_literal(html_file_path, output_file_path)
else:
    Import("env")
    pre_build_action(None, None, env)
