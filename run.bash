echo "Your OPENAI Token: $(cat .env | grep OPENAI_KEY= | cut -d '=' -f2)"
./build/cpp-discBot