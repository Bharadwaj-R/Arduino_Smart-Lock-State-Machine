enum SuperStateCheck
{
    Idle,
    Lock,
    Key1Press,
    Key2Press,
    Key3Press,
    Unlock
} SuperStatePassCheck;

enum SuperStateReset
{
    Resting,
    PasswordReset,
    FirstKeyPress,
    SecondKeyPress,
    ThirdKeyPress,
    PasswordSaved
} SuperStatePassReset;
